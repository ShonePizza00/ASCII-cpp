#include "Canvas.hpp"
#include "CanvasIterators.hpp"
#include <algorithm>
#include <fstream>
#include <utility>

namespace plotter
{

// Реализуйте методы класса Canvas в этом файле

	Canvas::Canvas(int width, int height, char background_char)
		: width_(width), height_(height), background_(background_char) {
		if (width_ <= 0 || height_ <= 0) {
			throw std::invalid_argument("Canvas dimensions must be positive");
		}
		data_.assign(width * height, background_char);
	}

	Canvas::Canvas(Canvas&& other) noexcept 
		: width_(other.width_), height_(other.height_), background_(other.background_), data_(std::move(other.data_)) {
	}

	Canvas& Canvas::operator=(const Canvas& other) {
		if (this != &other) {
			width_ = other.width_;
			height_ = other.height_;
			background_ = other.background_;
			data_ = other.data_;
		}
		return *this;
	}

	Canvas& Canvas::operator=(Canvas&& other) noexcept {
		if (this != &other) {
			width_ = std::exchange(other.width_, 0);
			height_ = std::exchange(other.height_, 0);
			background_ = other.background_;
			data_ = std::move(other.data_);
		}
		return *this;
	}

	int Canvas::Width() const noexcept {
		return width_;
	}

	int Canvas::Height() const noexcept {
		return height_;
	}

	int Canvas::Size() const noexcept {
		return data_.size();
	}

	const size_t Canvas::Index(int x, int y) const noexcept {
		return (size_t)(y) * width_ + x;
	}

	char& Canvas::at(int x, int y) {
		if (InBounds(x, y)) {
			return data_[Index(x, y)];
		}
		throw std::out_of_range("Canvas coordinates are out of bounds");
	}

	const char& Canvas::at(int x, int y) const {
		if (InBounds(x, y)) {
			return data_[Index(x, y)];
		}
		throw std::out_of_range("Canvas coordinates are out of bounds");
	}

	char& Canvas::operator()(int x, int y) noexcept {
		return data_[Index(x, y)];
	}

	const char& Canvas::operator()(int x, int y) const noexcept {
		return data_[Index(x, y)];
	}

	void Canvas::Clear(char fill_char) {
		background_ = fill_char;
		std::fill(data_.begin(), data_.end(), background_);
	}

	void Canvas::FillRegion(int x1, int y1, int x2, int y2, char fill_char) {
		if (x2 < x1) {
			std::swap(x1, x2);
		}
		if (y2 < y1) {
			std::swap(y1, y2);
		}
		x1 = std::clamp(x1, 0, width_-1);
		x2 = std::clamp(x2, 0, width_-1);
		y1 = std::clamp(y1, 0, height_-1);
		y2 = std::clamp(y2, 0, height_-1);

		for (int y = y1; y <= y2; ++y) {
			const size_t first_in_row = Index(x1, y);
			std::fill(data_.begin() + first_in_row, data_.begin() + first_in_row + x2 - x1 + 1, fill_char);
		}
	}

	bool Canvas::InBounds(int x, int y) const noexcept {
		return x >= 0 && y >= 0 && x < width_ && y < height_;
	}

	void Canvas::Render(std::ostream& os) const {
		for (int y = 0; y < height_; ++y) {
			const auto row_beg = data_.begin() + Index(0, y);
			os.write(&(*row_beg), width_);
			os.put('\n');
		}
		os.flush();
	}

	void Canvas::SaveToFile(const std::filesystem::path& filepath) const {
		std::filesystem::path complete_path = filepath;
		if (complete_path.is_relative()) {
			complete_path = std::filesystem::absolute(complete_path);
		}
		const auto parent = complete_path.parent_path();
		if (!parent.empty()) {
			std::filesystem::create_directories(parent);
		}
		std::ofstream out(complete_path);
		if (!out) {
			throw std::runtime_error("Cannot open file: " + complete_path.string());
		}
		Render(out);
	}

	void Canvas::SaveToFile(const std::string& filename) const {
		SaveToFile(std::filesystem::path(filename));
	}

	Canvas::RowIterator Canvas::RowBegin(int row) {
		if (row < 0 || row > height_) {
			throw std::out_of_range("Row is out of buonds");
		}
		return RowIterator(this, row, 0);
	}

	Canvas::RowIterator Canvas::RowEnd(int row) {
		if (row < 0 || row > height_) {
			throw std::out_of_range("Row is out of buonds");
		}
		return RowIterator(this, row, width_);
	}

	Canvas::ColumnIterator Canvas::ColBegin(int col) {
		if (col < 0 || col > width_) {
			throw std::out_of_range("Column is out of buonds");
		}
		return ColumnIterator(this, 0, col);
	}

	Canvas::ColumnIterator Canvas::ColEnd(int col) {
		if (col < 0 || col > width_) {
			throw std::out_of_range("Column is out of buonds");
		}
		return ColumnIterator(this, height_, col);
	}

	Canvas::PixelIterator Canvas::begin() {
		return PixelIterator(this, 0);
	}

	Canvas::PixelIterator Canvas::end() {
		return PixelIterator(this, data_.size());
	}
///////////////////////////////////////////////////////////////////
	/* 
	 * RowIterator vvv
	*/
	Canvas::RowIterator::RowIterator(Canvas* canvas, int row, int col) noexcept 
		: canvas_(canvas), row_(row), col_(col) {}

	Canvas::RowIterator::reference Canvas::RowIterator::operator*() const {
		return canvas_->at(col_, row_);
	}

	Canvas::RowIterator::pointer Canvas::RowIterator::operator->() const {
		return &(**this);
	}

	Canvas::RowIterator::reference Canvas::RowIterator::operator[](difference_type n) const {
		return *(*this + n);
	}

	Canvas::RowIterator& Canvas::RowIterator::operator++() {
		if (col_ < canvas_->width_) {
			++col_;
		}
		return *this;
	}

	Canvas::RowIterator Canvas::RowIterator::operator++(int) {
		auto old = *this;
		++(*this);
		return old;
	}

	Canvas::RowIterator& Canvas::RowIterator::operator--() {
		if (col_ > 0) {
			--col_;
		}
		return *this;
	}

	Canvas::RowIterator Canvas::RowIterator::operator--(int) {
		auto old = *this;
		--(*this);
		return old;
	}

	Canvas::RowIterator& Canvas::RowIterator::operator+=(difference_type n) {
		difference_type width = canvas_->width_;
		difference_type next = std::clamp(
			static_cast<difference_type>(col_) + n,
			static_cast<difference_type>(0),
			width);
		col_ = next;
		return *this;
	}

	Canvas::RowIterator& Canvas::RowIterator::operator-=(difference_type n) {
		return *this += -n;
	}
	
	/* 
	 * RowIterator ^^^
	*/
///////////////////////////////////////////////////////////////////
	/*
	 * ColIterator vvv
	*/
	Canvas::ColumnIterator::ColumnIterator(Canvas* canvas, int row, int col) noexcept
		: canvas_(canvas), row_(row), col_(col) {}

	Canvas::ColumnIterator::reference Canvas::ColumnIterator::operator*() const {
		return canvas_->at(col_, row_);
	}

	Canvas::ColumnIterator::pointer Canvas::ColumnIterator::operator->() const {
		return &(**this);
	}

	Canvas::ColumnIterator::reference Canvas::ColumnIterator::operator[](difference_type n) const {
		return *(*this + n);
	}

	Canvas::ColumnIterator& Canvas::ColumnIterator::operator++() {
		if (row_ < canvas_->height_) {
			++row_;
		}
		return *this;
	}

	Canvas::ColumnIterator Canvas::ColumnIterator::operator++(int) {
		auto old = *this;
		++(*this);
		return old;
	}

	Canvas::ColumnIterator& Canvas::ColumnIterator::operator--() {
		if (row_ > 0) {
			--row_;
		}
		return *this;
	}

	Canvas::ColumnIterator Canvas::ColumnIterator::operator--(int) {
		auto old = *this;
		--(*this);
		return old;
	}

	Canvas::ColumnIterator& Canvas::ColumnIterator::operator+=(difference_type n) {
		difference_type height = canvas_->height_;
		difference_type next = std::clamp(
			static_cast<difference_type>(row_) + n,
			static_cast<difference_type>(0),
			height);
		row_ = next;
		return *this;
	}

	Canvas::ColumnIterator& Canvas::ColumnIterator::operator-=(difference_type n) {
		return *this += -n;
	}

	/*
	 * ColIterator ^^^
	*/
///////////////////////////////////////////////////////////////////
	/*
	 * PixelIterator vvv
	*/
	Canvas::PixelIterator::PixelIterator(Canvas* canvas, size_t pos) noexcept
		: canvas_(canvas), pos_(pos) {}

	Canvas::PixelIterator::reference Canvas::PixelIterator::operator*() const {
		int x = (int)(pos_ % (size_t)(canvas_->Width()));
		int y = (int)(pos_ / (size_t)(canvas_->Width()));
		return canvas_->at(x, y);
	}
	Canvas::PixelIterator::pointer Canvas::PixelIterator::operator->() const {
		return &(**this);
	}

	Canvas::PixelIterator::reference Canvas::PixelIterator::operator[](difference_type n) const {
		return *(*this + n);
	}

	Canvas::PixelIterator& Canvas::PixelIterator::operator++() {
		size_t size = 
			static_cast<size_t>(canvas_->height_) * 
			static_cast<size_t>(canvas_->width_);
		if (pos_ < size) {
			++pos_;
		}
		return *this;
	}

	Canvas::PixelIterator Canvas::PixelIterator::operator++(int) {
		auto old = *this;
		++(*this);
		return old;
	}

	Canvas::PixelIterator& Canvas::PixelIterator::operator--() {
		if (pos_ > 0) {
			--pos_;
		}
		return *this;
	}

	Canvas::PixelIterator Canvas::PixelIterator::operator--(int) {
		auto old = *this;
		--(*this);
		return old;
	}

	Canvas::PixelIterator& Canvas::PixelIterator::operator+=(difference_type n) {
		difference_type size = 
			static_cast<difference_type>(canvas_->height_) * 
			static_cast<difference_type>(canvas_->width_);
		difference_type next = std::clamp(
			static_cast<difference_type>(pos_) + n,
			static_cast<difference_type>(0),
			size);
		pos_ = next;
		return *this;
	}

	Canvas::PixelIterator& Canvas::PixelIterator::operator-=(difference_type n) {
		return *this += -n;
	}
	
	/*
	 * PixelIterator ^^^
	*/


} // namespace plotter