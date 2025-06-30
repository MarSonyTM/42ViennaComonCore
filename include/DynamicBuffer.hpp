#ifndef DYNAMIC_BUFFER_HPP
# define DYNAMIC_BUFFER_HPP

# include <cstddef>  // for size_t
# include <string>   // for std::string
# include <cstring>  // for std::memcpy, std::memmove

class DynamicBuffer {
private:
    static const size_t INITIAL_SIZE = 1024;
    static const size_t MAX_SIZE = 16384; // 16KB max buffer size

    char*   _buffer;
    size_t  _size;
    size_t  _capacity;

    void grow() {
        size_t new_capacity = _capacity * 2;
        if (new_capacity > MAX_SIZE)
            new_capacity = MAX_SIZE;
        
        char* new_buffer = new char[new_capacity];
        std::memcpy(new_buffer, _buffer, _size);
        delete[] _buffer;
        _buffer = new_buffer;
        _capacity = new_capacity;
    }

public:
    DynamicBuffer() : _buffer(new char[INITIAL_SIZE]), _size(0), _capacity(INITIAL_SIZE) {}

    ~DynamicBuffer() {
        delete[] _buffer;
    }

    // Copy constructor (disabled)
    DynamicBuffer(const DynamicBuffer& other);

    // Assignment operator (disabled)
    DynamicBuffer& operator=(const DynamicBuffer& other);

    // Append data to buffer
    bool append(const char* data, size_t len) {
        if (_size + len > MAX_SIZE)
            return false;

        while (_size + len > _capacity)
            grow();

        std::memcpy(_buffer + _size, data, len);
        _size += len;
        return true;
    }

    // Get complete lines from buffer
    std::string getLine() {
        for (size_t i = 0; i < _size; ++i) {
            if (_buffer[i] == '\n' || (_buffer[i] == '\r' && i + 1 < _size && _buffer[i + 1] == '\n')) {
                size_t line_end = _buffer[i] == '\r' ? i : i + 1;
                std::string line(_buffer, line_end);
                
                // Remove the line from buffer
                size_t bytes_to_remove = _buffer[i] == '\r' ? i + 2 : i + 1;
                _size -= bytes_to_remove;
                std::memmove(_buffer, _buffer + bytes_to_remove, _size);
                
                return line;
            }
        }
        return "";
    }

    // Check if buffer has complete line
    bool hasCompleteLine() const {
        for (size_t i = 0; i < _size; ++i) {
            if (_buffer[i] == '\n' || (_buffer[i] == '\r' && i + 1 < _size && _buffer[i + 1] == '\n'))
                return true;
        }
        return false;
    }

    // Clear buffer
    void clear() {
        _size = 0;
    }

    // Get current size
    size_t size() const {
        return _size;
    }

    // Get remaining capacity
    size_t remainingCapacity() const {
        return _capacity - _size;
    }
};

#endif 