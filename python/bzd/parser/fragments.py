import re
from typing import Dict, Mapping, MutableMapping, Optional, TYPE_CHECKING

if TYPE_CHECKING:
	from bzd.parser.element import Element
	from bzd.parser.grammar import Grammar


class Attribute:

	def __init__(self, index: int, value: str):
		self.index = index
		self.value = value


Attributes = MutableMapping[str, Attribute]


class Fragment:
	"""
	A fragment is the smallest typed entity, that optionally contains attributes.
	It describes any entity discovered by the parser. 
	"""

	default: Dict[str, str] = {}

	def __init__(self, index: int, attrs: Mapping[str, str]) -> None:
		self.index = index
		self.attrs = self.default.copy()
		self.attrs.update(attrs)
		self.process()

	def merge(self, attrs: Attributes) -> None:
		"""
		Merge current attributes with existing ones
		"""
		for key, value in self.attrs.items():
			assert key not in attrs, "Attribute '{}' already set".format(key)
			attrs[key] = Attribute(index=self.index, value=value)

	def process(self) -> None:
		"""
		Post process a value discovered.
		"""
		pass

	def next(self, element: "Element", grammar: Optional["Grammar"]) -> "Element":
		"""
		Returns the next element for the next entity.
		This is where elements can be terminated and new ones can be generated.
		"""
		if grammar is not None:
			element.setGrammar(grammar)
		return element

	def __repr__(self) -> str:
		return "<{}:{} {}/>".format(self.__class__.__name__, self.index,
			" ".join(["{}='{}'".format(key, value) for key, value in self.attrs.items()]))


class FragmentComment(Fragment):
	"""
	Helper fragment for comments.
	"""

	def merge(self, attrs: Attributes) -> None:
		for key, value in self.attrs.items():

			# Remove empty lines at the begining and end
			value = re.sub(r"^(\s*\n)+", "", value)
			value = re.sub(r"(\n\s*)+$", "", value)

			# Remove common prefix and trailing spaces
			minTrailingSpaces = min([len(s) - len(s.lstrip(" ")) for s in value.split("\n")])
			updatedValue = "\n".join([s[minTrailingSpaces:].rstrip() for s in value.split("\n")])

			# Append the comments
			if key in attrs:
				attrs[key].value += "\n\n{}".format(updatedValue)
			else:
				attrs[key] = Attribute(index=self.index, value=updatedValue)


class FragmentNewElement(Fragment):
	"""
	Helper fragment to create a new element.
	"""

	def next(self, element: "Element", grammar: Optional["Grammar"]) -> "Element":
		return element.getSequence().makeElement()


class FragmentParentElement(Fragment):
	"""
	Helper fragment to continue on the parent element.
	"""

	def next(self, element: "Element", grammar: Optional["Grammar"]) -> "Element":
		return element.getSequence().getElement()


class FragmentNestedStart(Fragment):
	"""
	Helper fragment to start a nested sequence.
	"""

	nestedName = "nested"

	def next(self, element: "Element", grammar: Optional["Grammar"]) -> "Element":
		assert grammar is not None, "Grammar must be set"
		return element.makeElement(self.nestedName, grammar)


class FragmentNestedStop(Fragment):
	"""
	Helper fragment to stop a nested sequence.
	"""

	def next(self, element: "Element", grammar: Optional["Grammar"]) -> "Element":
		return element.getSequence().getElement().getSequence().makeElement()
