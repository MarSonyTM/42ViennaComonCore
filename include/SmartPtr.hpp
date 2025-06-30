#ifndef SMART_PTR_HPP
# define SMART_PTR_HPP

# include <cstddef>

template<typename T>
class SmartPtr {
private:
    T* _ptr;

public:
    // Constructor
    explicit SmartPtr(T* ptr = NULL) : _ptr(ptr) {}

    // Destructor
    ~SmartPtr() {
        delete _ptr;
    }

    // Copy constructor (disabled)
    SmartPtr(const SmartPtr& other);

    // Assignment operator (disabled)
    SmartPtr& operator=(const SmartPtr& other);

    // Pointer operators
    T& operator*() const { return *_ptr; }
    T* operator->() const { return _ptr; }
    T* get() const { return _ptr; }

    // Release ownership
    T* release() {
        T* tmp = _ptr;
        _ptr = NULL;
        return tmp;
    }

    // Reset pointer
    void reset(T* ptr = NULL) {
        if (_ptr != ptr) {
            delete _ptr;
            _ptr = ptr;
        }
    }
};

#endif 