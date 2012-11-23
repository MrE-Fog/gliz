///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Image Copyright (c) 2008 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2012-11-19
// Updated : 2012-11-19
// Licence : This source is under MIT licence
// File    : test/core/core_addressing.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <gli/core/addressing.hpp>
#include <gli/core/format.hpp>

int test_addressing_layers()
{
	int Error(0);

	struct test
	{
		test
		(
			gli::detail::storage::dimensions3_type const & Dimensions,
			gli::format const & Format,
			std::size_t const & Offset,
			std::size_t const & Size
		) :
			Dimensions(Dimensions),
			Format(Format),
			Offset(Offset),
			Size(Size)
		{}

		gli::detail::storage::dimensions3_type Dimensions;
		gli::format Format;
		std::size_t Offset;
		std::size_t Size;
	};

	std::vector<test> Tests;
	Tests.push_back(test(gli::detail::storage::dimensions3_type(4, 4, 1), gli::RGBA8U, 64, 128));
	Tests.push_back(test(gli::detail::storage::dimensions3_type(4, 4, 1), gli::RGB16F, 96, 192));
	Tests.push_back(test(gli::detail::storage::dimensions3_type(4, 4, 1), gli::RGBA32F, 256, 512));
	Tests.push_back(test(gli::detail::storage::dimensions3_type(4, 4, 1), gli::DXT1, 8, 16));
	Tests.push_back(test(gli::detail::storage::dimensions3_type(8, 8, 1), gli::DXT1, 32, 64));
	Tests.push_back(test(gli::detail::storage::dimensions3_type(4, 4, 1), gli::ATI1N_SNORM, 8, 16));

	for(std::size_t i = 0; i < Tests.size(); ++i)
	{
		gli::detail::storage Storage(
			2, 
			gli::faceCount(gli::FACE_DEFAULT), 
			1, 
			Tests[i].Dimensions, 
			gli::block_size(Tests[i].Format),
			gli::block_dimensions(Tests[i].Format));

		gli::detail::storage::size_type Offset = gli::detail::linearAddressing(Storage, 1, 0, 0);
		gli::detail::storage::size_type Size = Storage.size();

		Error += Offset == Tests[i].Offset ? 0 : 1;
		Error += Size == Tests[i].Size ? 0 : 1;
	}

	return Error;
}

int test_addressing_faces()
{
	int Error(0);

	struct test
	{
		test
		(
			gli::format const & Format,
			std::size_t const & Level,
			std::size_t const & Offset,
			std::size_t const & Size
		) :
			Format(Format),
			Level(Level),
			Offset(Offset),
			Size(Size)
		{}

		gli::format Format;
		std::size_t Level;
		std::size_t Offset;
		std::size_t Size;
	};

	std::vector<test> Tests;
	Tests.push_back(test(gli::RGBA8U, 0, 0, 340));
	Tests.push_back(test(gli::RGBA8U, 1, 256, 340));
    Tests.push_back(test(gli::R8U, 1, 64, 85));
	Tests.push_back(test(gli::RGBA8U, 3, 336, 340));
	Tests.push_back(test(gli::RGBA32F, 0, 0, 1360));
	Tests.push_back(test(gli::RGBA32F, 1, 1024, 1360));
	Tests.push_back(test(gli::DXT1, 0, 0, 56));
	Tests.push_back(test(gli::DXT1, 1, 32, 56));
    Tests.push_back(test(gli::DXT5, 1, 64, 112));

	for(std::size_t i = 0; i < Tests.size(); ++i)
	{
		gli::detail::storage Storage(
			1,
			gli::faceCount(gli::FACE_DEFAULT),
			4,
			gli::detail::storage::dimensions3_type(8, 8, 1),
			gli::block_size(Tests[i].Format),
			gli::block_dimensions(Tests[i].Format));

		gli::detail::storage::size_type Offset = gli::detail::linearAddressing(Storage, 0, 0, Tests[i].Level);
		gli::detail::storage::size_type Size = Storage.size();

		Error += Offset == Tests[i].Offset ? 0 : 1;
		Error += Size == Tests[i].Size ? 0 : 1;
	}

	return Error;
}

int test_addressing_levels()
{
	int Error(0);

	struct test
	{
		test
		(
			gli::format const & Format,
			std::size_t const & Level,
			std::size_t const & Offset,
			std::size_t const & Size
		) :
			Format(Format),
			Level(Level),
			Offset(Offset),
			Size(Size)
		{}

		gli::format Format;
		std::size_t Level;
		std::size_t Offset;
		std::size_t Size;
	};

	std::vector<test> Tests;
	Tests.push_back(test(gli::RGBA8U, 0, 0, 340));
	Tests.push_back(test(gli::RGBA8U, 1, 256, 340));
	Tests.push_back(test(gli::RGBA8U, 3, 336, 340));
	Tests.push_back(test(gli::RGBA32F, 0, 0, 1360));
	Tests.push_back(test(gli::RGBA32F, 1, 1024, 1360));
	Tests.push_back(test(gli::DXT1, 0, 0, 56));
	Tests.push_back(test(gli::DXT1, 1, 32, 56));

	for(std::size_t i = 0; i < Tests.size(); ++i)
	{
		gli::detail::storage Storage(
			1,
			gli::faceCount(gli::FACE_DEFAULT),
			4,
			gli::detail::storage::dimensions3_type(8, 8, 1),
			gli::block_size(Tests[i].Format),
			gli::block_dimensions(Tests[i].Format));

		gli::detail::storage::size_type Offset = gli::detail::linearAddressing(Storage, 0, 0, Tests[i].Level);
		gli::detail::storage::size_type Size = Storage.size();

		Error += Offset == Tests[i].Offset ? 0 : 1;
		Error += Size == Tests[i].Size ? 0 : 1;
	}

	return Error;
}

int main()
{
	int Error(0);

	Error += test_addressing_layers();
	Error += test_addressing_faces();
	Error += test_addressing_levels();

	return Error;
}
