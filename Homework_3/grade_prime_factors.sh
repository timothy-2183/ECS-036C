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
EXEC="${PWD}/prime_factors"
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
        # Remove trailing space if any
        local output="$(echo -e "${output_lines[${i}]}" | sed -e 's/[[:space:]]*$//')"
        if [[ "${output}" = "${expect_lines[${i}]}" ]]; then
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
run_test() {
    #1: cli arguments
    local args=("${@}")

    # These are global variables after the test has run so clear them out now
    unset STDOUT STDERR RET

    # Create temp files for getting stdout and stderr
    local outfile=$(mktemp)
    local errfile=$(mktemp)

    bash -c "${EXEC} ${args[*]}" \
        >${outfile} 2>${errfile}

    # Get the return status, stdout and stderr of the test case
    RET="${?}"
    STDOUT=$(cat "${outfile}")
    STDERR=$(cat "${errfile}")

    # Clean up temp files
    rm -f "${outfile}"
    rm -f "${errfile}"
}

#
# Test cases
#
TEST_CASES=()

## Error management args 1 (no arg)
TEST_CASES+=("err_no_arg")
err_no_arg() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test

    local line_array=()
    line_array+=("$(select_line "${STDERR}" "1")")
    local corr_array=()
    corr_array+=("Usage: ${EXEC} <number> <command> [<args>]")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Error management args 2 (one arg)
TEST_CASES+=("err_one_arg")
err_one_arg() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "4410"

    local line_array=()
    line_array+=("$(select_line "${STDERR}" "1")")
    local corr_array=()
    corr_array+=("Usage: ${EXEC} <number> <command> [<args>]")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Error management number (wrong number)
TEST_CASES+=("err_wrong_number")
err_wrong_number() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "toto" all

    local line_array=()
    line_array+=("$(select_line "${STDERR}" "1")")
    local corr_array=()
    corr_array+=("Invalid number")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Wrong command 1
TEST_CASES+=("err_wrong_command")
err_wrong_command() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "4410" toto

    local line_array=()
    line_array+=("$(select_line "${STDERR}" "1")")
    line_array+=("$(select_line "${STDERR}" "2")")
    local corr_array=()
    corr_array+=("Command 'toto' is invalid")
    corr_array+=("Possible commands are: all|min|max|near")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Wrong command 1 (near)
TEST_CASES+=("err_wrong_command_near")
err_wrong_command_near() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "4410" near

    local line_array=()
    line_array+=("$(select_line "${STDERR}" "1")")
    local corr_array=()
    corr_array+=("Command 'near' expects another argument: [+/-]prime")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Error code
TEST_CASES+=("err_code")
err_code() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "4410" near

    local line_array=()
    line_array+=("Return code: '${RET}'")
    local corr_array=()
    corr_array+=("Return code: '1'")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation: 4410 - all
TEST_CASES+=("4410_all")
4410_all() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "4410" all

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("2 (x1), 3 (x2), 5 (x1), 7 (x2),")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation: 4410 - min
TEST_CASES+=("4410_min")
4410_min() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "4410" min

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("2 (x1)")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation: 4410 - max
TEST_CASES+=("4410_max")
4410_max() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "4410" max

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("7 (x2)")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation: 4410 - near
TEST_CASES+=("4410_near")
4410_near() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "4410" near 5

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("5 (x1)")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation: 1431430 - all
TEST_CASES+=("1431430_all")
1431430_all() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "1431430" all

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("2 (x1), 5 (x1), 7 (x1), 11 (x2), 13 (x2),")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation: 1431430 - min
TEST_CASES+=("1431430_min")
1431430_min() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "1431430" min

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("2 (x1)")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation: 1431430 - max
TEST_CASES+=("1431430_max")
1431430_max() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "1431430" max

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("13 (x2)")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation: 1431430 - near
TEST_CASES+=("1431430_near")
1431430_near() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "1431430" near 7

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("7 (x1)")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation: 1431430 - near+
TEST_CASES+=("1431430_near_next")
1431430_near_next() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "1431430" near "+7"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("11 (x2)")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation: 1431430 - near-
TEST_CASES+=("1431430_near_prev")
1431430_near_prev() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "1431430" near "-7"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("5 (x1)")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation: 1431430 - near+ - no match
TEST_CASES+=("1431430_near_next_nomatch")
1431430_near_next_nomatch() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "1431430" near "+13"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("No match")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Result validation: 1431430 - near- - no match
TEST_CASES+=("1431430_near_prev_nomatch")
1431430_near_prev_nomatch() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "1431430" near "-2"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("No match")

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
