#ifndef UNIQUEPTR_H
#define UNIQUEPTR_H

#include <memory>

namespace custom_memory
{

template <class T, class Deleter = std::default_delete<T>> class UniquePtr
{
public:
    UniquePtr(T* ptr = nullptr, Deleter&& deleter = Deleter()) noexcept : ptr_{ptr}, deleter_{deleter}{}
    UniquePtr(UniquePtr &&ptr): ptr_{std::move(ptr)}{}
    UniquePtr(UniquePtr &ptr) = delete;
    UniquePtr& operator=(const UniquePtr& ptr) = delete;
    UniquePtr& operator=(const UniquePtr&& ptr) noexcept
    {
        if (this != ptr)
        {
            ptr_.reset(ptr.release());
            this.deleter_ = std::move(ptr->deleter_);
        }

        return *this;
    }

    //Modifiers
    T* release() noexcept
    {
        T* released = ptr_;
        ptr_ = nullptr;
        return released;
    }

    void reset( T* ptr = new T()) noexcept
    {
        T* oldPtr = this->ptr_;
        this->ptr_= ptr;

        if (oldPtr)
        {
            deleter_(oldPtr);
        }    
    }

    void swap( UniquePtr& other ) noexcept
    {
        if(ptr_ != other.ptr_)
        {
            T* auxPtr = this->release();
            ptr_ = other.release();
            other.ptr_ = auxPtr;

            auxPtr = nullptr;
        }

        Deleter& auxDel = deleter_;
        deleter_ = other.deleter_;
        other.deleter_ = auxDel;
    }

    //Observers
    T* get() const noexcept
    {
        return ptr_;
    }
    Deleter& get_deleter() noexcept
    {
        return deleter_;
    }
    const Deleter& get_deleter() const noexcept
    {
        return deleter_;
    }
    
    explicit operator bool() const noexcept
    {
        if (ptr_ != nullptr)
        {
            return true;
        }

        return false;
    }

    T& operator*() const noexcept
    {
        return *ptr_;
    }

    T* operator->() const noexcept
    {
        return ptr_;
    }

    T& operator[]( std::size_t i )
    {
        return ptr_[i];
    }

    ~UniquePtr()
    {
        this->deleter_(this->ptr_);
    }

private:
    T* ptr_;
    Deleter deleter_;
};

} // namespace custom_memory
#endif