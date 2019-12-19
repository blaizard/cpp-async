# [`bzd`](../../index.md)::[`Vector`](../index.md)

## `template<class T, SizeType N> class Vector`

#### Template
||||
|---:|:---|:---|
|class|T||
|SizeType|N||

|Function||
|:---|:---|
|[`Vector(Args &&... args)`](./index.md)||
|[`pushBack(const T & value)`](./index.md)|Adds a new element at the end of the vector, after its current last element.|
|[`capacity() const`](./index.md)|Returns the maximum number of elements the vector can hold.|
|[`clear()`](./index.md)|Removes all elements.|
|[`resize(const size_t n)`](./index.md)|Change the size of the vector.|
------
### `template<class... Args> explicit constexpr Vector(Args &&... args)`

#### Template
||||
|---:|:---|:---|
|class...|Args||
#### Parameters
||||
|---:|:---|:---|
|Args &&...|args||
------
### `constexpr void pushBack(const T & value)`
*From bzd::impl::Vector*

Adds a new element at the end of the vector, after its current last element.

The content of val is copied (or moved) to the new element.
#### Parameters
||||
|---:|:---|:---|
|const T &|value|Value to be copied (or moved) to the new element. |
------
### `constexpr SizeType capacity() const`
*From bzd::impl::Vector*

Returns the maximum number of elements the vector can hold.

Maximum number of element this vector can hold.
------
### `constexpr void clear()`
*From bzd::impl::Vector*

Removes all elements.
------
### `constexpr void resize(const size_t n)`
*From bzd::impl::Vector*

Change the size of the vector.
#### Parameters
||||
|---:|:---|:---|
|const size_t|n|The new size. Note, it must a be lower or equal to the capacity. |