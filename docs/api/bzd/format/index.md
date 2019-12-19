# [`bzd`](../../index.md)::[`format`](../index.md)

## ` format`


|Namespace||
|:---|:---|
|[`impl`](impl/index.md)||

|Function||
|:---|:---|
|[`toString(bzd::OStream & out, const F & f, Args &&... args)`](./index.md)|String formating.|
|[`toString(bzd::OStream & stream, const T & data)`](./index.md)||
|[`toString(bzd::OStream & stream, const T & data, const SizeType maxPrecision)`](./index.md)||
|[`toStringHex(bzd::OStream & stream, const T & data, const char *const digits)`](./index.md)||
|[`toStringOct(bzd::OStream & stream, const T & data)`](./index.md)||
|[`toStringBin(bzd::OStream & stream, const T & data)`](./index.md)||
|[`toString(bzd::OStream & stream, const bzd::StringView & data)`](./index.md)||
|[`toString(bzd::OStream & stream, const char c)`](./index.md)||
|[`toString(bzd::interface::String & str, Args &&... args)`](./index.md)||
------
### `template<class F, class... Args> constexpr void toString(bzd::OStream & out, const F & f, Args &&... args)`
String formating.

Lightweight and compilation time checking string formating utility. The syntax is compatible with Python format with some limitations.

```format_spec ::= [sign][#][.precision][type]
sign ::= "+" | "-" | " "
precision ::= integer
type ::= "b" | "d" | "f" | "o" | "x" | "X" | "f" | "p" | "%"
d Decimal integer
b Binary format
o Octal format
x Hexadecimal format (lower case)
X Hexadecimal format (upper case)
f Displays fixed point number (Default: 6)
p Pointer
% Percentage. Multiples by 100 and puts % at the end.
```

This is an after text
#### Template
||||
|---:|:---|:---|
|class F|None||
|class...|Args||
#### Parameters
||||
|---:|:---|:---|
|bzd::OStream &|out|Output stream where the formating string will be written to. |
|const F &|f|Compile-time string containing the format. |
|Args &&...|args|Arguments to be passed for the format. |
------
### `template<class T, typename bzd::typeTraits::enableIf< typeTraits::isIntegral< T >::value, T >::type *> constexpr void toString(bzd::OStream & stream, const T & data)`

#### Template
||||
|---:|:---|:---|
|class T|None||
|typename bzd::typeTraits::enableIf< typeTraits::isIntegral< T >::value, T >::type *|None||
#### Parameters
||||
|---:|:---|:---|
|bzd::OStream &|stream||
|const T &|data||
------
### `template<class T, typename bzd::typeTraits::enableIf< typeTraits::isFloatingPoint< T >::value, T >::type *> constexpr void toString(bzd::OStream & stream, const T & data, const SizeType maxPrecision)`

#### Template
||||
|---:|:---|:---|
|class T|None||
|typename bzd::typeTraits::enableIf< typeTraits::isFloatingPoint< T >::value, T >::type *|None||
#### Parameters
||||
|---:|:---|:---|
|bzd::OStream &|stream||
|const T &|data||
|const SizeType|maxPrecision||
------
### `template<class T, typename bzd::typeTraits::enableIf< typeTraits::isIntegral< T >::value, T >::type *> constexpr void toStringHex(bzd::OStream & stream, const T & data, const char *const digits)`

#### Template
||||
|---:|:---|:---|
|class T|None||
|typename bzd::typeTraits::enableIf< typeTraits::isIntegral< T >::value, T >::type *|None||
#### Parameters
||||
|---:|:---|:---|
|bzd::OStream &|stream||
|const T &|data||
|const char *const|digits||
------
### `template<class T, typename bzd::typeTraits::enableIf< typeTraits::isIntegral< T >::value, T >::type *> constexpr void toStringOct(bzd::OStream & stream, const T & data)`

#### Template
||||
|---:|:---|:---|
|class T|None||
|typename bzd::typeTraits::enableIf< typeTraits::isIntegral< T >::value, T >::type *|None||
#### Parameters
||||
|---:|:---|:---|
|bzd::OStream &|stream||
|const T &|data||
------
### `template<class T, typename bzd::typeTraits::enableIf< typeTraits::isIntegral< T >::value, T >::type *> constexpr void toStringBin(bzd::OStream & stream, const T & data)`

#### Template
||||
|---:|:---|:---|
|class T|None||
|typename bzd::typeTraits::enableIf< typeTraits::isIntegral< T >::value, T >::type *|None||
#### Parameters
||||
|---:|:---|:---|
|bzd::OStream &|stream||
|const T &|data||
------
### `void toString(bzd::OStream & stream, const bzd::StringView & data)`

#### Parameters
||||
|---:|:---|:---|
|bzd::OStream &|stream||
|const bzd::StringView &|data||
------
### `void toString(bzd::OStream & stream, const char c)`

#### Parameters
||||
|---:|:---|:---|
|bzd::OStream &|stream||
|const char|c||
------
### `template<class... Args> constexpr void toString(bzd::interface::String & str, Args &&... args)`

#### Template
||||
|---:|:---|:---|
|class...|Args||
#### Parameters
||||
|---:|:---|:---|
|bzd::interface::String &|str||
|Args &&...|args||