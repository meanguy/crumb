#! /usr/bin/env python3

import sys
from dataclasses import dataclass
from enum import Enum, auto
from typing import List

class TestCaseResult(Enum):
    pass_ = auto()
    fail = auto()
    skip = auto()


@dataclass
class TestResultLine:
    file: str
    lineno: int
    name: str
    result: TestCaseResult


if __name__ == "__main__":
    lines: List[TestResultLine] = []
    for current_line in sys.stdin:
        split = current_line.split(":")
        if len(split) != 4:
            continue

        file = split[0]
        lineno = int(split[1])
        name = split[2]
        result = {
            "PASS": TestCaseResult.pass_,
            "FAIL": TestCaseResult.fail,
            "IGNORE": TestCaseResult.skip,
        }[split[3][:-1]]

        lines.append(TestResultLine(file, lineno, name, result))

    if len(lines) == 0:
        print("No tests found.")

    num_results = {
        TestCaseResult.pass_: sum(1 for line in lines if line.result == TestCaseResult.pass_),
        TestCaseResult.fail: sum(1 for line in lines if line.result == TestCaseResult.fail),
        TestCaseResult.skip: sum(1 for line in lines if line.result == TestCaseResult.skip),
    }
    test_results = {
        TestCaseResult.pass_: [line for line in lines if line.result == TestCaseResult.pass_],
        TestCaseResult.fail: [line for line in lines if line.result == TestCaseResult.fail],
        TestCaseResult.skip: [line for line in lines if line.result == TestCaseResult.skip],
    }

    print(f"{lines[0]} results:")
    
    print(f"\t{num_results[TestCaseResult.pass_]}/{len(lines)} passing tests")
    for test_result in test_results[TestCaseResult.pass_]:
        print(f"\t\t[pass] {test_result.file}:{test_result.lineno}\t{test_result.name}")
    print("")

    print(f"\t{num_results[TestCaseResult.fail]}/{len(lines)} failing tests")
    for test_result in test_results[TestCaseResult.fail]:
        print(f"\t\t[fail] {test_result.file}:{test_result.lineno}\t{test_result.name}")
    print("")

    print(f"\t{num_results[TestCaseResult.skip]}/{len(lines)} skipped tests")
    for test_result in test_results[TestCaseResult.skip]:
        print(f"\t\t[skip] {test_result.file}:{test_result.lineno}\t{test_result.name}")
    print("")

    print(f"\t{num_results[TestCaseResult.pass_]} pass, {num_results[TestCaseResult.fail]} fail, {num_results[TestCaseResult.skip]} skip")