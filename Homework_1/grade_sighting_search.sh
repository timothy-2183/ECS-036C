#!/bin/bash

# Safer execution
# -e: exit immediately if a command fails
# -E: Safer -e option for traps
# -u: fail if a variable is used unset
# -o pipefail: exit immediately if command in a pipe fails
#set -eEuo pipefail
# -x: print each command before executing (great for debugging)
#set -x

# Convenient values
SCRIPT_NAME=$(basename $BASH_SOURCE)

# Default program values
EXEC="${PWD}/sighting_search"
DATASET_EXEC="${PWD}/create_dataset"
TEST_CASE="all"

#
# Logging helpers
#
log() {
    echo -e "${*}"
}
info() {
    log "Info: ${*}"
}
warning() {
    log "Warning: ${*}"
}
error() {
    log "Error: ${*}"
}
die() {
    error "${*}"
    exit 1
}

#
# Line comparison
#
select_line() {
    # 1: string
    # 2: line to select
    echo "$(echo "${1}" | sed "${2}q;d")"
}

fail() {
    # 1: got
    # 2: expected
    log "Fail: got '${1}' but expected '${2}'"
}

pass() {
    # got
    log "Pass: ${1}"
}

compare_lines() {
    # 1: output
    # 2: expected
    # 3: score (output)
    declare -a output_lines=("${!1}")
    declare -a expect_lines=("${!2}")
    local __score=$3
    local partial="0"

    # Amount of partial credit for each correct output line
    local step=$(bc -l <<< "1.0 / ${#expect_lines[@]}")

    # Compare lines, two by two
    for i in ${!output_lines[*]}; do
        # The right hand expression of pattern matching must be unquoted
        if [[ "${output_lines[${i}]}" =~ ${expect_lines[${i}]} ]]; then
            pass "${output_lines[${i}]}"
            partial=$(bc <<< "${partial} + ${step}")
        else
            fail "${output_lines[${i}]}" "${expect_lines[${i}]}" ]]
        fi
    done

    # Return final score
    eval ${__score}="'${partial}'"
}

#
# Run generic test case
#
run_test_case() {
    #1: search strategy
    #2: cli arguments
    local args=("${@}")
    local search="${args[0]}"
    local cli="${args[@]:1}"

    # These are global variables after the test has run so clear them out now
    unset STDOUT STDERR RET

    # Create temp files for getting stdout and stderr
    local outfile=$(mktemp)
    local errfile=$(mktemp)

    bash -c "echo -e \"${search}\\n\" | ${EXEC} ${cli}" \
        >${outfile} 2>${errfile}

    # Get the return status, stdout and stderr of the test case
    RET="${?}"
    STDOUT=$(cat "${outfile}")
    STDERR=$(cat "${errfile}")

    # Clean up temp files
    rm -f "${outfile}"
    rm -f "${errfile}"
}

gen_dataset() {
    #1: num sightings
    #2: num signatures
    #3: seed

    # Clean up any previous datasets
    rm -f *.dat

    # Run dataset generator with proper arguments
    "${DATASET_EXEC}" "${1}" "${2}" "${1}_${2}" "${3}"
}

#
# Test cases
#
TEST_CASES=()

## Error management args 1 (no arg)
TEST_CASES+=("err_no_arg")
err_no_arg() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test_case "l"

    local line_array=()
    line_array+=("$(select_line "${STDERR}" "1")")
    local corr_array=()
    corr_array+=("Usage: ${EXEC} <sighting_file.dat> <signature_file.dat> <result_file.dat>")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Error management args 2 (one arg)
TEST_CASES+=("err_one_arg")
err_one_arg() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test_case "l" "toto"

    local line_array=()
    line_array+=("$(select_line "${STDERR}" "1")")
    local corr_array=()
    corr_array+=("Usage: ${EXEC} <sighting_file.dat> <signature_file.dat> <result_file.dat>")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Error management args 3 (two arg)
TEST_CASES+=("err_two_arg")
err_two_arg() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test_case "l" "toto" "titi"

    local line_array=()
    line_array+=("$(select_line "${STDERR}" "1")")
    local corr_array=()
    corr_array+=("Usage: ${EXEC} <sighting_file.dat> <signature_file.dat> <result_file.dat>")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Error management files 1 (wrong sighting file)
TEST_CASES+=("err_wrong_sight_file")
err_wrong_sight_file() {
    log "--- Running test case: ${FUNCNAME} ---"
    gen_dataset 1 1 0
    run_test_case "l" "wrong_sight_file.dat" "signatures_1_1.dat" "res_1_1.dat"

    local line_array=()
    line_array+=("$(select_line "${STDERR}" "1")")
    local corr_array=()
    corr_array+=("Error: cannot open file wrong_sight_file.dat")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Error management files 2 (wrong signature file)
TEST_CASES+=("err_wrong_sig_file")
err_wrong_sig_file() {
    log "--- Running test case: ${FUNCNAME} ---"
    gen_dataset 1 1 0
    run_test_case "l" "sightings_1_1.dat" "wrong_sig_file.dat" "res_1_1.dat"

    local line_array=()
    line_array+=("$(select_line "${STDERR}" "1")")
    local corr_array=()
    corr_array+=("Error: cannot open file wrong_sig_file.dat")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Error management files 3 (wrong result file)
TEST_CASES+=("err_wrong_res_file")
err_wrong_res_file() {
    log "--- Running test case: ${FUNCNAME} ---"
    gen_dataset 1 1 0
    run_test_case "l" "sightings_1_1.dat" "signatures_1_1.dat" "/etc/passwd"

    local line_array=()
    line_array+=("$(select_line "${STDERR}" "1")")
    local corr_array=()
    corr_array+=("Error: cannot open file /etc/passwd")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Search choice 1 (one wrong choice)
TEST_CASES+=("err_wrong_choice_once")
err_wrong_choice_once() {
    log "--- Running test case: ${FUNCNAME} ---"
    gen_dataset 1 1 0
    run_test_case "j\nl" "sightings_1_1.dat" "signatures_1_1.dat" "res_1_1.dat"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    line_array+=("$(select_line "${STDERR}" "1")")
    local corr_array=()
    corr_array+=("Choice of search method ([l]inear, [b]inary)?")
    corr_array+=("Incorrect choice")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Search choice 2 (two wrong choices)
TEST_CASES+=("err_wrong_choice_twice")
err_wrong_choice_twice() {
    log "--- Running test case: ${FUNCNAME} ---"
    gen_dataset 1 1 0
    run_test_case "j\n2\nl" "sightings_1_1.dat" "signatures_1_1.dat" "res_1_1.dat"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    line_array+=("$(select_line "${STDERR}" "1")")
    line_array+=("$(select_line "${STDERR}" "2")")
    line_array+=("$(select_line "${STDOUT}" "2")")
    local corr_array=()
    corr_array+=("Choice of search method ([l]inear, [b]inary)?")
    corr_array+=("Incorrect choice")
    corr_array+=("Incorrect choice")
    corr_array+=("CPU time")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation linear-search 1 (dataset 100/100)
TEST_CASES+=("val_lin_100_100")
val_lin_100_100() {
    log "--- Running test case: ${FUNCNAME} ---"
    gen_dataset 100 100 0
    run_test_case "l" "sightings_100_100.dat" "signatures_100_100.dat" "res_100_100.dat"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "2")")
    line_array+=("$(cat res_100_100.dat)")
    local corr_array=()
    corr_array+=("CPU time: [0-9]+.[0-9]+ microseconds")
    corr_array+=("47")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation linear-search 2 (dataset 1000/100)
TEST_CASES+=("val_lin_1000_100")
val_lin_1000_100() {
    log "--- Running test case: ${FUNCNAME} ---"
    gen_dataset 1000 100 0
    run_test_case "l" "sightings_1000_100.dat" "signatures_1000_100.dat" "res_1000_100.dat"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "2")")
    line_array+=("$(cat res_1000_100.dat)")
    local corr_array=()
    corr_array+=("CPU time: [0-9]+.[0-9]+ microseconds")
    corr_array+=("94")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation linear-search 3 (dataset 100/1000)
TEST_CASES+=("val_lin_100_1000")
val_lin_100_1000() {
    log "--- Running test case: ${FUNCNAME} ---"
    gen_dataset 100 1000 0
    run_test_case "l" "sightings_100_1000.dat" "signatures_100_1000.dat" "res_100_1000.dat"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "2")")
    line_array+=("$(cat res_100_1000.dat)")
    local corr_array=()
    corr_array+=("CPU time: [0-9]+.[0-9]+ microseconds")
    corr_array+=("374")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation linear-search 4 (dataset 1000/1000)
TEST_CASES+=("val_lin_1000_1000")
val_lin_1000_1000() {
    log "--- Running test case: ${FUNCNAME} ---"
    gen_dataset 1000 1000 0
    run_test_case "l" "sightings_1000_1000.dat" "signatures_1000_1000.dat" "res_1000_1000.dat"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "2")")
    line_array+=("$(cat res_1000_1000.dat)")
    local corr_array=()
    corr_array+=("CPU time: [0-9]+.[0-9]+ microseconds")
    corr_array+=("931")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation binary-search 1 (dataset 100/100)
TEST_CASES+=("val_bin_100_100")
val_bin_100_100() {
    log "--- Running test case: ${FUNCNAME} ---"
    gen_dataset 100 100 0
    run_test_case "b" "sightings_100_100.dat" "signatures_100_100.dat" "res_100_100.dat"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "2")")
    line_array+=("$(cat res_100_100.dat)")
    local corr_array=()
    corr_array+=("CPU time: [0-9]+.[0-9]+ microseconds")
    corr_array+=("47")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation binary-search 2 (dataset 1000/100)
TEST_CASES+=("val_bin_1000_100")
val_bin_1000_100() {
    log "--- Running test case: ${FUNCNAME} ---"
    gen_dataset 1000 100 0
    run_test_case "b" "sightings_1000_100.dat" "signatures_1000_100.dat" "res_1000_100.dat"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "2")")
    line_array+=("$(cat res_1000_100.dat)")
    local corr_array=()
    corr_array+=("CPU time: [0-9]+.[0-9]+ microseconds")
    corr_array+=("94")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation binary-search 3 (dataset 100/1000)
TEST_CASES+=("val_bin_100_1000")
val_bin_100_1000() {
    log "--- Running test case: ${FUNCNAME} ---"
    gen_dataset 100 1000 0
    run_test_case "b" "sightings_100_1000.dat" "signatures_100_1000.dat" "res_100_1000.dat"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "2")")
    line_array+=("$(cat res_100_1000.dat)")
    local corr_array=()
    corr_array+=("CPU time: [0-9]+.[0-9]+ microseconds")
    corr_array+=("374")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation binary-search 4 (dataset 1000/1000)
TEST_CASES+=("val_bin_1000_1000")
val_bin_1000_1000() {
    log "--- Running test case: ${FUNCNAME} ---"
    gen_dataset 1000 1000 0
    run_test_case "b" "sightings_1000_1000.dat" "signatures_1000_1000.dat" "res_1000_1000.dat"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "2")")
    line_array+=("$(cat res_1000_1000.dat)")
    local corr_array=()
    corr_array+=("CPU time: [0-9]+.[0-9]+ microseconds")
    corr_array+=("931")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}
#
# Main functions
#
parse_argvs() {
    local OPTIND opt

    while getopts "h?s:t:" opt; do
        case "$opt" in
        h|\?)
            echo "${SCRIPT_NAME}: [-s <exec_path>] [-t <test_case>]" 1>&2
            exit 0
            ;;
        s)  EXEC="$(readlink -f ${OPTARG})"
            ;;
        t)  TEST_CASE="${OPTARG}"
            ;;
        esac
    done
}

check_vals() {
    # Check exec path
    [[ -x ${EXEC} ]] || \
        die "Cannot find executable '${EXEC}'"

    # Check test case
    [[ " ${TEST_CASES[@]} all " =~ " ${TEST_CASE} " ]] || \
        die "Cannot find test case '${TEST_CASE}'"
}

grade() {
    # Make testing directory
    local tmpdir=$(mktemp -d --tmpdir=.)
    cd ${tmpdir}

    # Run test case(s)
    if [[ "${TEST_CASE}" == "all" ]]; then
        # Run all test cases
    for t in "${TEST_CASES[@]}"; do
        ${t}
            log "\n"
    done
    else
        # Run specific test case
        ${TEST_CASE}
    fi

    # Cleanup testing directory
    cd ..
    rm -rf "${tmpdir}"
}

parse_argvs "$@"
check_vals
grade
