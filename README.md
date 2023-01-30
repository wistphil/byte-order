# byte-order
`byte-order` is a C++ library for encoding and decoding integral types to and from little and big endian. It provides an enumeration, `ByteOrder`, for checking the byte order of the system, which can be either `little` or `big`, and a set of encode and decode free frunctions.

The `ByteOrder` enumeration is defined as:
```
enum class ByteOrder
{
    little,
    big,
    native = // either 'little' or 'big'
};
```
The encode/decode function signatures are defined as:
(only `std::int32_t` is shown for brevity)
```
inline void encode_little(std::uint8_t * dst, std::int32_t value);
inline void encode_big(std::uint8_t * dst, std::int32_t value);

template <typename T>
auto decode_little(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int32_t>, T>;

template <typename T>
auto decode_big(std::uint8_t * src) -> std::enable_if_t<std::is_same_v<T, std::int32_t>, T>;
```
