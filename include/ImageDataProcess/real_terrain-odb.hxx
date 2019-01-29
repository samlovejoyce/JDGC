// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef REAL_TERRAIN_ODB_HXX
#define REAL_TERRAIN_ODB_HXX

// Begin prologue.
//
#include "blob-traits.hxx"
//
// End prologue.

#include <odb/version.hxx>

#if (ODB_VERSION != 20400UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "real_terrain.hxx"

#include <memory>
#include <cstddef>

#include <odb/core.hxx>
#include <odb/traits.hxx>
#include <odb/callback.hxx>
#include <odb/wrapper-traits.hxx>
#include <odb/pointer-traits.hxx>
#include <odb/container-traits.hxx>
#include <odb/no-op-cache-traits.hxx>
#include <odb/result.hxx>
#include <odb/no-id-object-result.hxx>

#include <odb/details/unused.hxx>
#include <odb/details/shared-ptr.hxx>

namespace odb
{
  // real_terrain
  //
  template <>
  struct class_traits< ::real_terrain >
  {
    static const class_kind kind = class_object;
  };

  template <>
  class access::object_traits< ::real_terrain >
  {
    public:
    typedef ::real_terrain object_type;
    typedef ::real_terrain* pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef void id_type;

    static const bool auto_id = false;

    static const bool abstract = false;

    static id_type
    id (const object_type&);

    typedef
    no_id_pointer_cache_traits<pointer_type>
    pointer_cache_traits;

    typedef
    no_id_reference_cache_traits<object_type>
    reference_cache_traits;

    static void
    callback (database&, object_type&, callback_event);

    static void
    callback (database&, const object_type&, callback_event);
  };
}

#include <odb/details/buffer.hxx>

#include <odb/mysql/version.hxx>
#include <odb/mysql/forward.hxx>
#include <odb/mysql/binding.hxx>
#include <odb/mysql/mysql-types.hxx>
#include <odb/mysql/query.hxx>

namespace odb
{
  // real_terrain
  //
  template <typename A>
  struct query_columns< ::real_terrain, id_mysql, A >
  {
    // xblocksno
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        unsigned int,
        mysql::id_ulong >::query_type,
      mysql::id_ulong >
    xblocksno_type_;

    static const xblocksno_type_ xblocksno;

    // yblocksno
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        unsigned int,
        mysql::id_ulong >::query_type,
      mysql::id_ulong >
    yblocksno_type_;

    static const yblocksno_type_ yblocksno;

    // xblocksize
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        short unsigned int,
        mysql::id_ushort >::query_type,
      mysql::id_ushort >
    xblocksize_type_;

    static const xblocksize_type_ xblocksize;

    // yblocksize
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        short unsigned int,
        mysql::id_ushort >::query_type,
      mysql::id_ushort >
    yblocksize_type_;

    static const yblocksize_type_ yblocksize;

    // zdata
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        ::buffer,
        mysql::id_blob >::query_type,
      mysql::id_blob >
    zdata_type_;

    static const zdata_type_ zdata;
  };

  template <typename A>
  const typename query_columns< ::real_terrain, id_mysql, A >::xblocksno_type_
  query_columns< ::real_terrain, id_mysql, A >::
  xblocksno (A::table_name, "`xblocksno`", 0);

  template <typename A>
  const typename query_columns< ::real_terrain, id_mysql, A >::yblocksno_type_
  query_columns< ::real_terrain, id_mysql, A >::
  yblocksno (A::table_name, "`yblocksno`", 0);

  template <typename A>
  const typename query_columns< ::real_terrain, id_mysql, A >::xblocksize_type_
  query_columns< ::real_terrain, id_mysql, A >::
  xblocksize (A::table_name, "`xblocksize`", 0);

  template <typename A>
  const typename query_columns< ::real_terrain, id_mysql, A >::yblocksize_type_
  query_columns< ::real_terrain, id_mysql, A >::
  yblocksize (A::table_name, "`yblocksize`", 0);

  template <typename A>
  const typename query_columns< ::real_terrain, id_mysql, A >::zdata_type_
  query_columns< ::real_terrain, id_mysql, A >::
  zdata (A::table_name, "`zdata`", 0);

  template <typename A>
  struct pointer_query_columns< ::real_terrain, id_mysql, A >:
    query_columns< ::real_terrain, id_mysql, A >
  {
  };

  template <>
  class access::object_traits_impl< ::real_terrain, id_mysql >:
    public access::object_traits< ::real_terrain >
  {
    public:
    struct image_type
    {
      // xblocksno
      //
      unsigned int xblocksno_value;
      my_bool xblocksno_null;

      // yblocksno
      //
      unsigned int yblocksno_value;
      my_bool yblocksno_null;

      // xblocksize
      //
      unsigned short xblocksize_value;
      my_bool xblocksize_null;

      // yblocksize
      //
      unsigned short yblocksize_value;
      my_bool yblocksize_null;

      // zdata
      //
      details::buffer zdata_value;
      unsigned long zdata_size;
      my_bool zdata_null;

      std::size_t version;
    };

    using object_traits<object_type>::id;

    static bool
    grow (image_type&,
          my_bool*);

    static void
    bind (MYSQL_BIND*,
          image_type&,
          mysql::statement_kind);

    static bool
    init (image_type&,
          const object_type&,
          mysql::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    typedef mysql::no_id_object_statements<object_type> statements_type;

    typedef mysql::query_base query_base_type;

    static const std::size_t column_count = 5UL;
    static const std::size_t id_column_count = 0UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    public:
  };

  template <>
  class access::object_traits_impl< ::real_terrain, id_common >:
    public access::object_traits_impl< ::real_terrain, id_mysql >
  {
  };

  // real_terrain
  //
}

#include "real_terrain-odb.ixx"

#include <odb/post.hxx>

#endif // REAL_TERRAIN_ODB_HXX
