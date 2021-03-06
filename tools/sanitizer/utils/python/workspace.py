import os
import json
import re
from typing import Iterable, List, Optional
from pathlib import Path
from .filter import Filter
from gitignore_parser import parse_gitignore


class Files:

	def __init__(self,
		path: Path,
		include: Optional[List[str]] = None,
		exclude: Optional[List[str]] = None,
		useGitignore: bool = False) -> None:
		configRaw = Path(__file__).parent.parent.parent.joinpath(".sanitizer.json").read_text()
		config = json.loads(configRaw)
		self.path = path
		self.workspace = Files._findWorkspace(path)
		self.exclude = Filter(config.get("exclude", []) + ([] if exclude is None else exclude))
		self.include = Filter(["**"] if include is None else include)
		self.gitignoreMatches = parse_gitignore(self.workspace / ".gitignore") if useGitignore else None

	@staticmethod
	def _findWorkspace(path: Path) -> Path:
		workspace = path
		while True:
			if workspace.joinpath("WORKSPACE").is_file():
				return workspace
			assert workspace != workspace.parent, "Could not find any workspace directory associated with {}".format(
				path)
			workspace = workspace.parent

	"""
	Return the root directory of the workspace
	"""

	def getWorkspace(self) -> Path:
		return self.workspace

	def data(self, relative: bool = False) -> Iterable[Path]:
		for (dirpath, dirnames, filenames) in os.walk(self.path):
			# Ignore symlinks and gitignore directories
			if self.gitignoreMatches:
				dirnames[:] = [
					d for d in dirnames if not Path(dirpath).joinpath(d).is_symlink()
					and not self.gitignoreMatches(Path(dirpath).joinpath(d).as_posix())
				]
			for filename in filenames:
				path = Path(dirpath).joinpath(filename)
				if self.gitignoreMatches is None or not self.gitignoreMatches(path.as_posix()):
					relativePath = path.relative_to(self.workspace)
					if not self.exclude.match(relativePath):
						if self.include.match(relativePath):
							yield relativePath if relative else path
