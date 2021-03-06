import argparse
import os
import sys
import bzd.utils.worker
from pathlib import Path
from yapf.yapflib.yapf_api import FormatFile
from tools.sanitizer.utils.python.workspace import Files
from typing import TextIO

configFile = os.path.join(os.path.dirname(__file__), "yapf.ini")


def yapfWorker(path: str, stdout: TextIO) -> None:
	result = FormatFile(path, style_config=configFile, in_place=True, logger=stdout)
	assert result[1] == "utf-8", "Wrong encoding {}, must be utf-8".format(result[1])


if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="Wrapper for mypy")
	parser.add_argument("workspace", type=Path, help="Workspace to be processed.")

	args = parser.parse_args()

	files = Files(args.workspace, include=[
		"**/*.py",
	], exclude=[
		"**tools/bzd/generator/yaml**",
	])

	# Process the varous files
	worker = bzd.utils.worker.Worker(yapfWorker)
	worker.start()
	for path in files.data():
		worker.add(path.as_posix())

	isSuccess = True
	for result in worker.data():
		if not result.isSuccess():
			isSuccess = False
			print(result.getOutput(), end="")

	worker.stop()

	sys.exit(0 if isSuccess else 1)
