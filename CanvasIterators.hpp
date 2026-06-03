#pragma once
#include "Canvas.hpp"

namespace plotter {

class Canvas::RowIterator {
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = char;
	using difference_type = std::ptrdiff_t;
	using pointer = char*;
	using reference = char&;
	// Реализуйте методы класса
	RowIterator(Canvas* canvas = nullptr, int row = 0, int col = 0) noexcept;
	
	reference operator*() const;
	pointer operator->() const;
	reference operator[](difference_type n) const;

	RowIterator& operator++();
	RowIterator operator++(int);
	RowIterator& operator--();
	RowIterator operator--(int);
	RowIterator& operator+=(difference_type n);
	RowIterator& operator-=(difference_type n);

	friend RowIterator operator+(RowIterator it, difference_type n) {
		return it += n;
	}

	friend RowIterator operator+(difference_type n, RowIterator it) {
		return it += n;
	}

	friend RowIterator operator-(RowIterator it, difference_type n) {
		return it -= n;
	}

	friend difference_type operator-(const RowIterator& lhs, const RowIterator& rhs) {
		return lhs.col_ - rhs.col_;
	}

	friend bool operator==(const RowIterator& lhs, const RowIterator& rhs) {
		return lhs.canvas_ == rhs.canvas_ && lhs.col_ == rhs.col_ && lhs.row_ == rhs.row_;
	}

	friend bool operator!= (const RowIterator& lhs, const RowIterator& rhs) {
		return !(lhs == rhs);
	}

	friend bool operator<(const RowIterator& lhs, const RowIterator& rhs) {
		return lhs.col_ < rhs.col_;
	}

	friend bool operator>(const RowIterator& lhs, const RowIterator& rhs) {
		return rhs < lhs;
	}

	friend bool operator<=(const RowIterator& lhs, const RowIterator& rhs) {
		return !(rhs < lhs);
	}

	friend bool operator>=(const RowIterator& lhs, const RowIterator& rhs) {
		return !(lhs < rhs);
	}

private:
	Canvas* canvas_;
	int row_;
	int col_;
};

class Canvas::ColumnIterator {
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = char;
	using difference_type = std::ptrdiff_t;
	using pointer = char*;
	using reference = char&;
	// Реализуйте методы класса
	ColumnIterator(Canvas* canvas = nullptr, int row = 0, int col = 0) noexcept;
	
	reference operator*() const;
	pointer operator->() const;
	reference operator[](difference_type n) const;

	ColumnIterator& operator++();
	ColumnIterator operator++(int);
	ColumnIterator& operator--();
	ColumnIterator operator--(int);
	ColumnIterator& operator+=(difference_type n);
	ColumnIterator& operator-=(difference_type n);

	friend ColumnIterator operator+(ColumnIterator it, difference_type n) {
		return it += n;
	}

	friend ColumnIterator operator+(difference_type n, ColumnIterator it) {
		return it += n;
	}

	friend ColumnIterator operator-(ColumnIterator it, difference_type n) {
		return it -= n;
	}

	friend difference_type operator-(const ColumnIterator& lhs, const ColumnIterator& rhs) {
		return lhs.col_ - rhs.col_;
	}

	friend bool operator==(const ColumnIterator& lhs, const ColumnIterator& rhs) {
		return lhs.canvas_ == rhs.canvas_ && lhs.col_ == rhs.col_ && lhs.row_ == rhs.row_;
	}

	friend bool operator!= (const ColumnIterator& lhs, const ColumnIterator& rhs) {
		return !(lhs == rhs);
	}

	friend bool operator<(const ColumnIterator& lhs, const ColumnIterator& rhs) {
		return lhs.col_ < rhs.col_;
	}

	friend bool operator>(const ColumnIterator& lhs, const ColumnIterator& rhs) {
		return rhs < lhs;
	}

	friend bool operator<=(const ColumnIterator& lhs, const ColumnIterator& rhs) {
		return !(rhs < lhs);
	}

	friend bool operator>=(const ColumnIterator& lhs, const ColumnIterator& rhs) {
		return !(lhs < rhs);
	}

private:
	Canvas* canvas_;
	int col_;
	int row_;
};

class Canvas::PixelIterator {
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = char;
	using difference_type = std::ptrdiff_t;
	using pointer = char*;
	using reference = char&;
	// Реализуйте методы класса
	PixelIterator(Canvas* canvas = nullptr, size_t pos = 0) noexcept;
	
	reference operator*() const;
	pointer operator->() const;
	reference operator[](difference_type n) const;

	PixelIterator& operator++();
	PixelIterator operator++(int);
	PixelIterator& operator--();
	PixelIterator operator--(int);
	PixelIterator& operator+=(difference_type n);
	PixelIterator& operator-=(difference_type n);

	friend PixelIterator operator+(PixelIterator it, difference_type n) {
		return it += n;
	}

	friend PixelIterator operator+(difference_type n, PixelIterator it) {
		return it += n;
	}

	friend PixelIterator operator-(PixelIterator it, difference_type n) {
		return it -= n;
	}

	friend difference_type operator-(const PixelIterator& lhs, const PixelIterator& rhs) {
		return lhs.pos_ - rhs.pos_;
	}

	friend bool operator==(const PixelIterator& lhs, const PixelIterator& rhs) {
		return lhs.canvas_ == rhs.canvas_ && lhs.pos_ == rhs.pos_;
	}

	friend bool operator!= (const PixelIterator& lhs, const PixelIterator& rhs) {
		return !(lhs == rhs);
	}

	friend bool operator<(const PixelIterator& lhs, const PixelIterator& rhs) {
		return lhs.pos_ < rhs.pos_;
	}

	friend bool operator>(const PixelIterator& lhs, const PixelIterator& rhs) {
		return rhs < lhs;
	}

	friend bool operator<=(const PixelIterator& lhs, const PixelIterator& rhs) {
		return !(rhs < lhs);
	}

	friend bool operator>=(const PixelIterator& lhs, const PixelIterator& rhs) {
		return !(lhs < rhs);
	}

private:
	Canvas* canvas_;
	size_t pos_;
};


} // namespace plotter