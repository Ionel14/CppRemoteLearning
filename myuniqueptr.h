#ifndef MYUNIQUEPTR_H
#define MYUNIQUEPTR_H

#include <cstddef>
#include <utility>

namespace smartHome{
    template <typename T>
    class MyUniquePtr {
    private:
        T* ptr;

    public:
        // Constructor
        explicit MyUniquePtr(T* p);

        // Destructor
        ~MyUniquePtr();

        // Move constructor
        MyUniquePtr(MyUniquePtr&& other) noexcept;

        // Move assignment operator
        MyUniquePtr& operator=(MyUniquePtr&& other) noexcept;

        // Copy and copy assignment are deleted
        MyUniquePtr(const MyUniquePtr&) = delete;
        MyUniquePtr& operator=(const MyUniquePtr&) = delete;

        // Overload dereference operator
        T& operator*() const;

        // Overload arrow operator
        T* operator->() const;

        // Get the raw pointer
        T* get() const;

        // Release ownership of the pointer
        T* release();

        // Reset the pointer
        void reset(T* p = nullptr);

        // Swap pointers
        void swap(MyUniquePtr& other) noexcept;

        // Check if there is an associated managed object
        explicit operator bool() const;

        // Array version: provides indexed access to the managed array
        T& operator[](std::size_t index) const;
    };
}

#endif // MYUNIQUEPTR_H
