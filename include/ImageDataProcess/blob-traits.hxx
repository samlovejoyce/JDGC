#ifndef BLOB_TRAITS_HXX
#define BLOB_TRAITS_HXX

#include <vector>
#include <cstring> // std::memcpy

#include <odb/mysql/traits.hxx>
#include "real_terrain.hxx"

namespace odb
{
	namespace mysql
	{

		template <typename T>
		struct value_traits<std::vector<T>, id_blob>
		{
		public:
			typedef std::vector<T> value_type;
			typedef std::vector<T> query_type;
			typedef details::buffer image_type;

			static void
				set_value(value_type& v,
					const details::buffer& b,
					std::size_t n,
					bool is_null)
			{
				if (!is_null)
				{
					const T* p = reinterpret_cast<const T*> (b.data());
					v.assign(p, p + n / sizeof(T));
				}
				else
					v.clear();
			}

			static void
				set_image(details::buffer& b,
					std::size_t& n,
					bool& is_null,
					const value_type& v)
			{
				is_null = false;
				n = v.size() * sizeof(T);

				if (n > b.capacity())
					b.capacity(n);

				if (n != 0)
					std::memcpy(b.data(), &v.front(), n);
			}
		};
	}
}
#endif // !BLOB_TRAITS_HXX
