# Channels

Channels are ways to communicate to the external environement.
It can be used as a communication mean through local buses (I2C, UART...) or more widely via ethernet or internet.

A channel consists of 2 layers, the adapter and the transport layer.
The adapter layer has the role to serialize/deserialize the data as well as consistency/errors checks at the data level.
The tranport layer has the role to transport data blobs via a bus.

## Declaration

```
registry {
	i2c = I2C(role = "master", speed = 1000000);
}

channel I2CTempSensor {
	adapter = I2CDevice(address = 12, addressing = 10/*bit*/);
	transport = &i2c;
}
```

## Adapter

The adapter implementation would be defined as follow:

```
interface I2CDevice {
	struct Data {
		integer data;
	}

	method serialize(Data) -> Result<Sequence<Byte>>;
	method deserialize(Sequence<Byte>) -> Result<Data>;
}
```

or a more complex adpater could be defined as follow:

```
interface I2CDevice {
	struct Data {
		integer destinationId;
		Sequence<Byte, 4> payload;
		integer crc [min = 0, max = 255];
		timestamp time;
	}

	method serialize(Data) -> Result<Sequence<Byte>>;
	method deserialize(Sequence<Byte>) -> Result<Data>;
}
```

By default serialize and deserialize templated functions will be autogenerated,
however the user can specialize their implementation if needed.
Here is an example of could look such function:

```c++
// Auto-generate serialization function
template <typename T>
Result<Sequence<Byte>> serialize(const T& data) const
{
	return bzd::Serialize<T>(data);
}

// Specialized function adds a byte in from of the payload
template <>
Result<Sequence<Byte>> serialize<uint8_t>(const uint8_t& data) const
{
	return Sequence<Byte>{0x2a, data};
}
```

## Transport

The transport implementation must have the following interface:

```
interface Transport {

	// Service related
	method start() -> Result<void>;
	method stop() -> Result<void>;
	method getStatus() -> Status;

	// Data
	method read() -> Result<Sequence<Byte>>;
	method write(Sequence<Byte>) -> Result<void>;
}
```

## Channel Interface

The user will only have access to the channel via its interface, which abstract all the transportation details underneath.
This interface is auto generated from the channel object.

```
interface Channel {
	struct Data {
		integer temperature;
		timestamp time;
	}

	read() ->
}
```