#ifndef SMARTHOME_UNIQUE_PTR_H_
#define SMARTHOME_UNIQUE_PTR_H_

#include <iostream>
#include <vector>
#include <memory>

namespace smartHome {

template<class T, class Deleter = std::default_delete<T>>
class UniquePtr {
public:
  constexpr UniquePtr() noexcept;
  constexpr UniquePtr(std::nullptr_t) noexcept;
  explicit UniquePtr(T* data, const Deleter& deleter = Deleter()) noexcept;
  UniquePtr(UniquePtr&& other) noexcept;
  UniquePtr(const UniquePtr&) = delete;

  ~UniquePtr();

  UniquePtr& operator=(std::nullptr_t) noexcept;
  UniquePtr& operator=(UniquePtr&& other) noexcept;
  UniquePtr& operator=(const UniquePtr&) = delete;

  T* release() noexcept;
  void reset(T* ptr = nullptr) noexcept;
  void swap(UniquePtr& other) noexcept;

  T* get() const noexcept;
  Deleter& get_deleter() noexcept;
  const Deleter& get_deleter() const noexcept;
  explicit operator bool() const noexcept;

  T& operator*() const noexcept;
  T* operator->() const noexcept;

  T& operator[](std::size_t i) const;

private:
  T* data;
  Deleter deleter;
};


template<class  T, class Deleter>
constexpr UniquePtr<T, Deleter>::UniquePtr() noexcept : data(nullptr) {}

template<class  T, class Deleter>
constexpr UniquePtr<T, Deleter>::UniquePtr(std::nullptr_t) noexcept : data(nullptr) {}

template<class  T, class Deleter>
UniquePtr<T, Deleter>::UniquePtr(T* data, const Deleter& deleter) noexcept : data(data), deleter(deleter) {}

template<class  T, class Deleter>
UniquePtr<T, Deleter>::UniquePtr(UniquePtr&& other) noexcept : data(other.get()), deleter(other.get_deleter()) {}


template<class  T, class Deleter>
UniquePtr<T, Deleter>::~UniquePtr() {
  if (data != nullptr) {
    deleter(get());
  }
}


template<class  T, class Deleter>
UniquePtr<T, Deleter>& UniquePtr<T, Deleter>::operator=(std::nullptr_t) noexcept {
  reset();
  return *this;
}

template<class  T, class Deleter>
UniquePtr<T, Deleter>& UniquePtr<T, Deleter>::operator=(UniquePtr<T, Deleter>&& other) noexcept {
  reset(other.release());
  deleter = other.get_deleter();
  return *this;
}


template<class  T, class Deleter>
T* UniquePtr<T, Deleter>::release() noexcept {
  T* copy = data;
  data = nullptr;
  return copy;
}

template<class  T, class Deleter>
void UniquePtr<T, Deleter>::reset(T* ptr) noexcept {
  T* old_ptr = data;
  data = ptr;
  if(old_ptr) {
    deleter(old_ptr);
  }
}

template<class  T, class Deleter>
void UniquePtr<T, Deleter>::swap(UniquePtr& other) noexcept {
  UniquePtr copy;
  copy = std::move(*this);
  *this = std::move(other);
  other = std::move(copy);
}


template<class  T, class Deleter>
T* UniquePtr<T, Deleter>::get() const noexcept {
  return data;
}

template<class  T, class Deleter>
Deleter& UniquePtr<T, Deleter>::get_deleter() noexcept {
  return deleter;
}

template<class  T, class Deleter>
const Deleter& UniquePtr<T, Deleter>::get_deleter() const noexcept {
  return deleter;
}

template<class  T, class Deleter>
UniquePtr<T, Deleter>::operator bool() const noexcept {
  return data;
}


template<class  T, class Deleter>
T& UniquePtr<T, Deleter>::operator*() const noexcept {
  return *data;
}

template<class  T, class Deleter>
T* UniquePtr<T, Deleter>::operator->() const noexcept {
  return data;
}


template<class  T, class Deleter>
T& UniquePtr<T, Deleter>::operator[](std::size_t i) const {
  if (i < data.size()) {
    return data[i];
  } else {
    throw std::invalid_argument("The given index has to be positive and smaller than the array size");
  }
}

} // namespace smarthome
#endif  // SMARTHOME_UNIQUE_PTR_H_