///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2015 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file gli/core/texture.hpp
/// @date 2013-02-05 / 2013-02-05
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "image.hpp"

namespace gli
{
	enum target
	{
		TARGET_NONE,
		TARGET_1D,
		TARGET_1D_ARRAY,
		TARGET_2D,
		TARGET_2D_ARRAY,
		TARGET_3D,
		TARGET_CUBE,
		TARGET_CUBE_ARRAY
	};

	class texture
	{
	public:
		typedef size_t size_type;
		typedef gli::format format_type;
		typedef storage::dim_type dim_type;

		texture();

		texture(
			gli::target Target,
			size_type const & Layers,
			size_type const & Faces,
			size_type const & Levels,
			format_type const & Format,
			storage::dim_type const & Dimensions);

		texture(
			texture const & Texture,
			gli::target Target,
			format_type const & Format,
			size_type BaseLayer, size_type MaxLayer,
			size_type BaseFace, size_type MaxFace,
			size_type BaseLevel, size_type MaxLevel);

		texture(
			texture const & Texture,
			gli::target Target);

		texture(
			gli::target Target,
			storage const & Storage);

		texture(
			gli::target Target,
			storage const & Storage,
			format_type const & Format,
			size_type BaseLayer, size_type MaxLayer,
			size_type BaseFace, size_type MaxFace,
			size_type BaseLevel, size_type MaxLevel);

		virtual ~texture(){}

		bool empty() const;
		format_type format() const;
		
		size_type baseLayer() const;
		size_type maxLayer() const;
		size_type layers() const;

		size_type baseFace() const;
		size_type maxFace() const;
		size_type faces() const;

		size_type baseLevel() const;
		size_type maxLevel() const;
		size_type levels() const;

		dim_type dimensions(size_type Level = 0) const;

		size_type size() const;
		template <typename genType>
		size_type size() const;

		void * data();
		template <typename genType>
		genType * data();
		void const * data() const;
		template <typename genType>
		genType const * data() const;

		void clear();
		template <typename genType>
		void clear(genType const & Texel);

		gli::target target() const{return this->Target;}

		operator storage() const{return this->Storage;}

	protected:
		storage Storage;
		gli::target const Target;
		format_type const Format;
		size_type const BaseLayer;
		size_type const MaxLayer;
		size_type const BaseFace;
		size_type const MaxFace;
		size_type const BaseLevel;
		size_type const MaxLevel;
		void * const Data;
		size_type const Size;

	private:
		void * const compute_data();
		size_type compute_size() const;
	};

	inline texture::texture()
		: Target(TARGET_NONE)
		, Format(static_cast<gli::format>(FORMAT_INVALID))
		, BaseLayer(0), MaxLayer(0)
		, BaseFace(0), MaxFace(0)
		, BaseLevel(0), MaxLevel(0)
		, Data(nullptr)
		, Size(0)
	{}

	inline texture::texture
	(
		gli::target Target,
		size_type const & Layers,
		size_type const & Faces,
		size_type const & Levels,
		format_type const & Format,
		storage::dim_type const & Dimensions
	)
		: Storage(Layers, Faces, Levels, Format, Dimensions)
		, Target(Target)
		, Format(Format)
		, BaseLayer(0), MaxLayer(Layers - 1)
		, BaseFace(0), MaxFace(Faces - 1)
		, BaseLevel(0), MaxLevel(Levels - 1)
		, Data(this->compute_data())
		, Size(this->compute_size())
	{}
/*
	inline texture::texture
	(
		texture const & Texture,
		gli::target Target,
		format_type const & Format,
		size_type BaseLayer, size_type MaxLayer,
		size_type BaseFace, size_type MaxFace,
		size_type BaseLevel, size_type MaxLevel
	)
	{

	}
*/
	inline texture::texture
	(
		texture const & Texture,
		gli::target Target
	)
		: Storage(Texture.Storage)
		, Target(Target)
		, Format(Texture.format())
		, BaseLayer(Texture.baseLayer()), MaxLayer(Texture.maxLayer())
		, BaseFace(Texture.baseFace()), MaxFace(Texture.maxFace())
		, BaseLevel(Texture.baseLevel()), MaxLevel(Texture.maxLevel())
		, Data(this->compute_data())
		, Size(this->compute_size())
	{
		assert(Target != TARGET_1D || (Target == TARGET_1D && this->layers() == 1 && this->faces() == 1 && this->dimensions().y == 1 && this->dimensions().z == 1));
		assert(Target != TARGET_1D_ARRAY || (Target == TARGET_1D_ARRAY && this->layers() >= 1 && this->faces() == 1 && this->dimensions().y == 1 && this->dimensions().z == 1));
		assert(Target != TARGET_2D || (Target == TARGET_2D && this->layers() == 1 && this->faces() == 1 && this->dimensions().y >= 1 && this->dimensions().z == 1));
		assert(Target != TARGET_2D_ARRAY || (Target == TARGET_2D_ARRAY && this->layers() >= 1 && this->faces() == 1 && this->dimensions().y >= 1 && this->dimensions().z == 1));
		assert(Target != TARGET_3D || (Target == TARGET_3D && this->layers() == 1 && this->faces() == 1 && this->dimensions().y >= 1 && this->dimensions().z >= 1));
		assert(Target != TARGET_CUBE || (Target == TARGET_CUBE && this->layers() == 1 && this->faces() >= 1 && this->dimensions().y >= 1 && this->dimensions().z == 1));
		assert(Target != TARGET_CUBE_ARRAY || (Target == TARGET_CUBE_ARRAY && this->layers() >= 1 && this->faces() >= 1 && this->dimensions().y >= 1 && this->dimensions().z == 1));
	}

	inline texture::texture
	(
		gli::target target,
		storage const & Storage
	)
		: Storage(Storage)
		, Target(Target)
		, Format(Storage.format())
		, BaseLayer(0), MaxLayer(Storage.layers() - 1)
		, BaseFace(0), MaxFace(Storage.faces() - 1)
		, BaseLevel(0), MaxLevel(Storage.levels() - 1)
		, Data(this->compute_data())
		, Size(this->compute_size())
	{}

	inline texture::texture
	(
		gli::target target,
		storage const & Storage,
		format_type const & Format,
		size_type BaseLayer, size_type MaxLayer,
		size_type BaseFace, size_type MaxFace,
		size_type BaseLevel, size_type MaxLevel
	)
		: Storage(Storage)
		, Target(Target)
		, Format(Format)
		, BaseLayer(BaseLayer), MaxLayer(MaxLayer)
		, BaseFace(BaseFace), MaxFace(MaxFace)
		, BaseLevel(BaseLevel), MaxLevel(MaxLevel)
		, Data(this->compute_data())
		, Size(this->compute_size())
	{}

	inline texture::size_type texture::size() const
	{
		assert(!this->empty());

		return this->Size;
	}

	template <typename genType>
	inline texture::size_type texture::size() const
	{
		assert(!this->empty());
		assert(block_size(this->Storage.format()) >= sizeof(genType));

		return this->size() / sizeof(genType);
	}

	inline void * texture::data()
	{
		return this->Data;
	}

	inline void const * texture::data() const
	{
		return this->Data;
	}

	template <typename genType>
	inline genType * texture::data()
	{
		assert(!this->empty());
		assert(block_size(this->format()) >= sizeof(genType));

		return reinterpret_cast<genType *>(this->data());
	}

	template <typename genType>
	inline genType const * texture::data() const
	{
		assert(!this->empty());
		assert(block_size(this->format()) >= sizeof(genType));

		return reinterpret_cast<genType const *>(this->data());
	}

	inline bool texture::empty() const
	{
		return this->Storage.empty();
	}

	inline texture::format_type texture::format() const
	{
		return this->Format;
	}

	inline texture::dim_type texture::dimensions(size_type Level) const
	{
		assert(!this->empty());

		return this->Storage.dimensions(this->baseLevel() + Level);
	}

	inline texture::size_type texture::baseLayer() const
	{
		return this->BaseLayer;
	}

	inline texture::size_type texture::maxLayer() const
	{
		return this->MaxLayer;
	}

	inline texture::size_type texture::layers() const
	{
		return this->maxLayer() - this->baseLayer() + 1;
	}

	inline texture::size_type texture::baseFace() const
	{
		return this->BaseFace;
	}

	inline texture::size_type texture::maxFace() const
	{
		return this->MaxFace;
	}

	inline texture::size_type texture::faces() const
	{
		//assert(this->maxFace() - this->baseFace() + 1 == 1);
		return this->maxFace() - this->baseFace() + 1;
	}

	inline texture::size_type texture::baseLevel() const
	{
		return this->BaseLevel;
	}

	inline texture::size_type texture::maxLevel() const
	{
		return this->MaxLevel;
	}

	inline texture::size_type texture::levels() const
	{
		return this->maxLevel() - this->baseLevel() + 1;
	}

	inline void texture::clear()
	{
		memset(this->data<glm::byte>(), 0, this->size<glm::byte>());
	}

	template <typename genType>
	inline void texture::clear(genType const & Texel)
	{
		assert(!this->empty());
		assert(block_size(this->Storage.format()) == sizeof(genType));

		genType* Data = this->data<genType>();
		size_type const TexelCount = this->size<genType>();

		for(size_type TexelIndex = 0; TexelIndex < TexelCount; ++TexelIndex)
			*(Data + TexelIndex) = Texel;
	}

	inline void * const texture::compute_data()
	{
		size_type const offset = detail::imageAddressing(
			this->Storage, this->baseLayer(), this->baseFace(), this->baseLevel());

		return this->Storage.data() + offset;
	}

	inline texture::size_type texture::compute_size() const
	{
		assert(!this->empty());

		return this->Storage.layer_size(
			this->baseFace(), this->maxFace(),
			this->baseLevel(), this->maxLevel()) * this->layers();
	}
}//namespace gli

#include "texture1d.hpp"
#include "texture1d_array.hpp"
#include "texture2d.hpp"
#include "texture2d_array.hpp"
#include "texture3d.hpp"
#include "texture_cube.hpp"
#include "texture_cube_array.hpp"

#include "addressing.hpp"

#include "texture1d.inl"
#include "texture1d_array.inl"
#include "texture2d.inl"
#include "texture2d_array.inl"
#include "texture3d.inl"
#include "texture_cube.inl"
#include "texture_cube_array.inl"
