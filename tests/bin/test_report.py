#! /usr/bin/env python3

import sys
from dataclasses import dataclass
from enum import Enum, auto
from typing import List, Optional

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
    errmsg: Optional[str]


if __name__ == "__main__":
    lines: List[TestResultLine] = []
    for current_line in sys.stdin:
        split = current_line.replace("\n", "").split(":")
        if len(split) < 4:
            break

        file = split[0]
        lineno = int(split[1])
        name = split[2]
        result = {
            "PASS": TestCaseResult.pass_,
            "FAIL": TestCaseResult.fail,
            "IGNORE": TestCaseResult.skip,
        }[split[3]]

        errmsg = None
        if result == TestCaseResult.fail and len(split) == 5:
            errmsg = split[4]

        lines.append(TestResultLine(file, lineno, name, result, errmsg=errmsg))

    if len(lines) == 0:
        print("No tests found.")
        sys.exit(0)

    test_results = {
        TestCaseResult.pass_: [line for line in lines if line.result == TestCaseResult.pass_],
        TestCaseResult.fail: [line for line in lines if line.result == TestCaseResult.fail],
        TestCaseResult.skip: [line for line in lines if line.result == TestCaseResult.skip],
    }
    num_results = {state: len(lines) for state, lines in test_results.items()}
    
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

    if num_results[TestCaseResult.fail] > 0:
        sys.exit(1)

    sys.exit(0)
