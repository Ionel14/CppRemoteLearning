#ifndef SMARTHOME_UNIQUE_PTR_H_
#define SMARTHOME_UNIQUE_PTR_H_

#include <iostream>
#include <vector>

namespace smarthome {

template<typename T>
class UniquePtr {
public:
  constexpr UniquePtr() noexcept;
  constexpr UniquePtr(std::nullptr_t) noexcept;
  explicit UniquePtr(T* data) noexcept;

  ~UniquePtr();

  UniquePtr& operator=(UniquePtr&& other) noexcept;
  UniquePtr& operator=(std::nullptr_t) noexcept;
  UniquePtr& operator=(const UniquePtr&) = delete;

  T* release() noexcept;
  void reset(T* ptr) noexcept;
  void swap(UniquePtr& other) noexcept;

  T* get() const noexcept;
  explicit operator bool() const noexcept;

  T& operator*() const noexcept;
  T* operator->() const noexcept;

  T& operator[](std::size_t i) const;

private:
  T* data;
};


template<typename  T>
constexpr UniquePtr<T>::UniquePtr() noexcept : data(nullptr) {}

template<typename  T>
constexpr UniquePtr<T>::UniquePtr(std::nullptr_t) noexcept : data(nullptr) {}

template<typename  T>
UniquePtr<T>::UniquePtr(T* data) noexcept : data(data) {}


template<typename  T>
UniquePtr<T>::~UniquePtr() {
  if (data != nullptr) {
    delete data;
  }
}


template<typename  T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept {
  reset(other.release());
  return *this;
}

template<typename  T>
UniquePtr<T>& UniquePtr<T>::operator=(std::nullptr_t) noexcept {
  reset(nullptr);
  return *this;
}


template<typename  T>
T* UniquePtr<T>::release() noexcept {
  T* copy = data;
  data = nullptr;
  return copy;
}

template<typename  T>
void UniquePtr<T>::reset(T* ptr) noexcept {
  T* old_ptr = data;
  data = ptr;
  if(old_ptr) {
    delete old_ptr;
  }
}

template<typename  T>
void UniquePtr<T>::swap(UniquePtr& other) noexcept {
  UniquePtr copy;
  copy = std::move(*this);
  *this = std::move(other);
  other = std::move(copy);
}


template<typename  T>
T* UniquePtr<T>::get() const noexcept {
  return data;
}

template<typename  T>
UniquePtr<T>::operator bool() const noexcept {
  return data;
}


template<typename  T>
T& UniquePtr<T>::operator*() const noexcept {
  return *data;
}

template<typename  T>
T* UniquePtr<T>::operator->() const noexcept {
  return data;
}


template<typename  T>
T& UniquePtr<T>::operator[](std::size_t i) const {
  if (i < data.size()) {
    return data[i];
  } else {
    throw std::invalid_argument("The given index has to be positive and smaller than the array size");
  }
}

} // namespace smarthome
#endif  // SMARTHOME_UNIQUE_PTR_H_