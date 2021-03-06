import typing

from bzd.parser.fragments import Fragment, Attributes, Attribute
from bzd.parser.grammar import Grammar
if typing.TYPE_CHECKING:
	from bzd.parser.parser import Parser


class Sequence:

	def __init__(self) -> None:
		self.list: typing.List["Element"] = []

	def iterate(self) -> typing.Iterator["Element"]:
		for element in self.list:
			if not element.isEmpty():
				yield element

	def merge(self, sequence: "Sequence") -> None:
		self.list += sequence.list

	def __repr__(self) -> str:
		listStr = []
		for element in self.list:
			formattedStr = "- {}".format("\n  ".join(repr(element).split("\n")))
			listStr.append(formattedStr)
		return "\n".join(listStr)


class SequenceParser(Sequence):
	"""
	This represents a sequence of Elements.
	"""

	def __init__(self, parser: "Parser", grammar: Grammar, parent: typing.Optional["Element"]) -> None:
		super().__init__()
		self.parser = parser
		self.grammar = grammar
		self.parent = parent

	def makeElement(self) -> "Element":
		element = Element(parser=self.parser, grammar=self.grammar, parent=self)
		self.list.append(element)
		return element

	def getGrammar(self) -> Grammar:
		return self.grammar

	def getElement(self) -> "Element":
		assert self.parent, "This sequence is at the top level."
		return self.parent


class Element:

	def __init__(self, parser: "Parser", grammar: Grammar, parent: typing.Optional[SequenceParser] = None) -> None:
		self.parser = parser
		self.grammar = grammar
		self.parent = parent
		self.attrs: Attributes = {}
		self.sequences: typing.Dict[str, SequenceParser] = {}

	def isEmpty(self) -> bool:
		"""
		Check wether or not an element is empty. Empty means with no data.
		"""
		return (len(self.attrs.keys()) + len(self.sequences.keys())) == 0

	def getAttrs(self) -> typing.Mapping[str, Attribute]:
		"""
		Return the attributes as a dictionary.
		"""
		return self.attrs

	def getAttr(self, name: str) -> Attribute:
		"""
		Return a specific name attribute value
		"""
		assert name in self.attrs, "Attribute '{}' is not present in '{}'".format(name, str(self))
		return self.attrs[name]

	def getAttrValue(self, name: str, default: typing.Optional[str] = None) -> typing.Optional[str]:
		"""
		Return a specific name attribute value
		"""
		if name in self.attrs:
			return self.attrs[name].value
		return default

	def isAttr(self, name: str) -> bool:
		"""
		Check if an attribute is present
		"""
		if name in self.attrs:
			return True
		return False

	def add(self, fragment: Fragment) -> None:
		"""
		Add a new fragment to this element.
		"""
		fragment.merge(self.attrs)

	def setGrammar(self, grammar: Grammar) -> None:
		"""
		Update the grammar of the current element.
		"""
		self.grammar = grammar

	def getGrammar(self) -> Grammar:
		return self.grammar

	def makeElement(self, kind: str, grammar: Grammar) -> "Element":
		if kind not in self.sequences:
			self.sequences[kind] = SequenceParser(parser=self.parser, grammar=grammar, parent=self)
		return self.sequences[kind].makeElement()

	def getSequence(self) -> SequenceParser:
		assert self.parent is not None, "reached parent element"
		assert isinstance(self.parent,
			SequenceParser), "parent must be a sequence, instead {}".format(type(self.parent))
		return self.parent

	def isNestedSequence(self, kind: str) -> bool:
		return bool(kind in self.sequences)

	def getNestedSequence(self, kind: str) -> typing.Optional[SequenceParser]:
		return self.sequences.get(kind, None)

	def getNestedSequences(self) -> typing.Iterator[typing.Tuple[str, SequenceParser]]:
		for kind, sequence in self.sequences.items():
			yield kind, sequence

	def __repr__(self) -> str:
		content = "<Element {}/>".format(" ".join(
			["{}:{}=\"{}\"".format(key, attr.index, attr.value) for key, attr in self.attrs.items()]))

		for kind, sequence in self.sequences.items():
			content += "\n{}:\n{}".format(kind, repr(sequence))

		return content
