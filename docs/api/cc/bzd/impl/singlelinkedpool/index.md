# [`bzd`](../../../index.md)::[`impl`](../../index.md)::[`SingleLinkedPool`](../index.md)

## `template<class T, class CapacityType> class SingleLinkedPool`

#### Template
||||
|---:|:---|:---|
|class|T||
|class|CapacityType||

|Function||
|:---|:---|
|[`SingleLinkedPool(const bzd::Span< Element > data)`](./index.md)||
|[`at(const SizeType index)`](./index.md)||
|[`at(const SizeType index) const`](./index.md)||
|[`back()`](./index.md)||
|[`back() const`](./index.md)||
|[`begin()`](./index.md)||
|[`begin() const`](./index.md)||
|[`capacity() const`](./index.md)||
|[`cbegin() const`](./index.md)||
|[`cend() const`](./index.md)||
|[`data()`](./index.md)||
|[`data() const`](./index.md)||
|[`empty() const`](./index.md)||
|[`empty() const`](./index.md)||
|[`end()`](./index.md)||
|[`end() const`](./index.md)||
|[`find(const DataType & item, const SizeType start) const`](./index.md)||
|[`front()`](./index.md)||
|[`front() const`](./index.md)||
|[`getIndex(const Element & element) const`](./index.md)||
|[`operator!=(const SelfType & rhs) const`](./index.md)||
|[`operator==(const SelfType & rhs) const`](./index.md)||
|[`operator[](const SizeType index)`](./index.md)||
|[`operator[](const SizeType index) const`](./index.md)||
|[`release(Element & element)`](./index.md)||
|[`reserve()`](./index.md)||
|[`size() const`](./index.md)||
|[`Span()`](./index.md)||
|[`Span(DataType *const data, const SizeType size)`](./index.md)||
|[`Span(const Span< bzd::typeTraits::RemoveConst< DataType >> & span)`](./index.md)||
|[`toStream(std::ostream & os)`](./index.md)||

|Typedef||
|:---|:---|
|[`ConstIterator`](./index.md)|alias of [`bzd::iterator::Contiguous`](../../iterator/contiguous/index.md)|
|[`Element`](./index.md)|alias of [`bzd::impl::SingleLinkedPoolElement`](../singlelinkedpoolelement/index.md)|
|[`Iterator`](./index.md)|alias of [`bzd::iterator::Contiguous`](../../iterator/contiguous/index.md)|
|[`Parent`](./index.md)|alias of [`bzd::Span`](../../span/index.md)|

|Variable||
|:---|:---|
|[`npos`](./index.md)||
|[`npos`](./index.md)||
------
### `explicit constexpr SingleLinkedPool(const bzd::Span< Element > data)`

#### Parameters
||||
|---:|:---|:---|
|const bzd::Span< Element >|data||
------
### `template<class Q, bzd::typeTraits::EnableIf<!Q::value, void > *> constexpr DataType & at(const SizeType index)`
*From bzd::Span*


#### Template
||||
|---:|:---|:---|
|class Q|None||
|bzd::typeTraits::EnableIf<!Q::value, void > *|None||
#### Parameters
||||
|---:|:---|:---|
|const SizeType|index||
------
### `constexpr const T & at(const SizeType index) const`
*From bzd::Span*


#### Parameters
||||
|---:|:---|:---|
|const SizeType|index||
------
### `template<class Q, bzd::typeTraits::EnableIf<!Q::value, void > *> constexpr DataType & back()`
*From bzd::Span*


#### Template
||||
|---:|:---|:---|
|class Q|None||
|bzd::typeTraits::EnableIf<!Q::value, void > *|None||
------
### `constexpr const DataType & back() const`
*From bzd::Span*


------
### `template<class Q, bzd::typeTraits::EnableIf<!Q::value, void > *> constexpr Iterator begin()`
*From bzd::Span*


#### Template
||||
|---:|:---|:---|
|class Q|None||
|bzd::typeTraits::EnableIf<!Q::value, void > *|None||
------
### `constexpr ConstIterator begin() const`
*From bzd::Span*


------
### `constexpr CapacityType capacity() const`

------
### `constexpr ConstIterator cbegin() const`
*From bzd::Span*


------
### `constexpr ConstIterator cend() const`
*From bzd::Span*


------
### `template<class Q, bzd::typeTraits::EnableIf<!Q::value, void > *> constexpr DataType * data()`
*From bzd::Span*


#### Template
||||
|---:|:---|:---|
|class Q|None||
|bzd::typeTraits::EnableIf<!Q::value, void > *|None||
------
### `constexpr const DataType * data() const`
*From bzd::Span*


------
### `constexpr bool empty() const`

------
### `constexpr bool empty() const`
*From bzd::Span*


------
### `template<class Q, bzd::typeTraits::EnableIf<!Q::value, void > *> constexpr Iterator end()`
*From bzd::Span*


#### Template
||||
|---:|:---|:---|
|class Q|None||
|bzd::typeTraits::EnableIf<!Q::value, void > *|None||
------
### `constexpr ConstIterator end() const`
*From bzd::Span*


------
### `constexpr SizeType find(const DataType & item, const SizeType start) const`
*From bzd::Span*


#### Parameters
||||
|---:|:---|:---|
|const DataType &|item||
|const SizeType|start||
------
### `template<class Q, bzd::typeTraits::EnableIf<!Q::value, void > *> constexpr DataType & front()`
*From bzd::Span*


#### Template
||||
|---:|:---|:---|
|class Q|None||
|bzd::typeTraits::EnableIf<!Q::value, void > *|None||
------
### `constexpr const DataType & front() const`
*From bzd::Span*


------
### `constexpr CapacityType getIndex(const Element & element) const`

#### Parameters
||||
|---:|:---|:---|
|const Element &|element||
------
### `constexpr bool operator!=(const SelfType & rhs) const`
*From bzd::Span*


#### Parameters
||||
|---:|:---|:---|
|const SelfType &|rhs||
------
### `constexpr bool operator==(const SelfType & rhs) const`
*From bzd::Span*


#### Parameters
||||
|---:|:---|:---|
|const SelfType &|rhs||
------
### `template<class Q, bzd::typeTraits::EnableIf<!Q::value, void > *> constexpr DataType & operator[](const SizeType index)`
*From bzd::Span*


#### Template
||||
|---:|:---|:---|
|class Q|None||
|bzd::typeTraits::EnableIf<!Q::value, void > *|None||
#### Parameters
||||
|---:|:---|:---|
|const SizeType|index||
------
### `constexpr const DataType & operator[](const SizeType index) const`
*From bzd::Span*


#### Parameters
||||
|---:|:---|:---|
|const SizeType|index||
------
### `constexpr void release(Element & element)`
Release an element from the pool
#### Parameters
||||
|---:|:---|:---|
|Element &|element||
------
### `constexpr Element & reserve()`
Reserve an element from the free list (if any)
------
### `constexpr SizeType size() const`
*From bzd::Span*


------
### `constexpr Span()`
*From bzd::Span*


------
### `constexpr Span(DataType *const data, const SizeType size)`
*From bzd::Span*


#### Parameters
||||
|---:|:---|:---|
|DataType *const|data||
|const SizeType|size||
------
### `template<class Q, bzd::typeTraits::EnableIf< Q::value, void > *> constexpr Span(const Span< bzd::typeTraits::RemoveConst< DataType >> & span)`
*From bzd::Span*


#### Template
||||
|---:|:---|:---|
|class Q|None||
|bzd::typeTraits::EnableIf< Q::value, void > *|None||
#### Parameters
||||
|---:|:---|:---|
|const Span< bzd::typeTraits::RemoveConst< DataType >> &|span||
------
### `void toStream(std::ostream & os)`

#### Parameters
||||
|---:|:---|:---|
|std::ostream &|os||
------
### `typedef ConstIterator`
*From bzd::Span*


------
### `typedef Element`

------
### `typedef Iterator`
*From bzd::Span*


------
### `typedef Parent`

------
### `static constexpr const CapacityType npos`

------
### `static constexpr const SizeType npos`
*From bzd::Span*

