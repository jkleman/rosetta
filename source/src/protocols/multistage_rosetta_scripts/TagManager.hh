// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file protocols/multistage_rosetta_scripts/TagManager.hh
/// @brief This class was designed to help the MRSJobQueen handle tags for many input jobs
/// @author Jack Maguire


#ifndef INCLUDED_protocols_multistage_rosetta_scripts_TagManager_HH
#define INCLUDED_protocols_multistage_rosetta_scripts_TagManager_HH

#include <utility/VirtualBase.hh>
#include <protocols/multistage_rosetta_scripts/TagManager.fwd.hh>

#include <protocols/jd3/strong_types.hh>


#include <basic/datacache/DataMap.hh>

#include <utility/tag/Tag.fwd.hh>


#include <core/types.hh> // AUTO IWYU For Size


#ifdef    SERIALIZATION
// Cereal headers
#include <cereal/types/polymorphic.fwd.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/vector.hpp>
#endif // SERIALIZATION

namespace protocols {
namespace multistage_rosetta_scripts {

///@brief This class does not fail when you try to add an element that already exists. Instead, it just keeps the older element.
class NoFailDataMap : public basic::datacache::DataMap {
public:

	NoFailDataMap() :
		basic::datacache::DataMap()
	{}

	bool add(
		std::string const & type,
		std::string const & name,
		utility::VirtualBaseOP const op
	) override;

};

struct ParsedTagCache{
	ParsedTagCache(
		jd3::PrelimJobNodeID const input_pose_id_in,
		NoFailDataMapOP data_map_in,
		TagMapOP mover_tags_in,
		TagMapOP filter_tags_in
	) :
		input_pose_id( input_pose_id_in ),
		data_map( data_map_in ),
		mover_tags( mover_tags_in ),
		filter_tags( filter_tags_in )
	{}

	jd3::PrelimJobNodeID input_pose_id;
	NoFailDataMapOP data_map;
	TagMapOP mover_tags;
	TagMapOP filter_tags;

};

class TagManager : public utility::VirtualBase {
public:
	TagManager();
	TagManager( core::Size num_input_pose_ids );

	~TagManager() override;

	void set_num_input_pose_ids( core::Size num_input_pose_ids );

	void set_common_data_tags( std::list< utility::tag::TagCOP > && tags_in_order ){
		tag_list_for_input_pose_id_[ 0 ]->splice(
			tag_list_for_input_pose_id_[ 0 ]->begin(),
			tags_in_order
		);
	}

	void set_common_data_tags( std::list< utility::tag::TagCOP > const & tags_in_order ){
		std::list< utility::tag::TagCOP > temp_copy = tags_in_order;
		set_common_data_tags( std::move( temp_copy ) );
	}

	///@brief register all tags that are not present in common tags
	void register_data_tags_for_input_pose_id(
		jd3::PrelimJobNodeID input_pose_id,
		std::list< utility::tag::TagCOP > const & tags_in_order
	);

	///@brief overload of register_data_tags_for_input_pose_id that uses move semantics
	void register_data_tags_for_input_pose_id(
		jd3::PrelimJobNodeID input_pose_id,
		std::list< utility::tag::TagCOP > && tags_in_order
	);

	ParsedTagCacheOP generate_data_for_input_pose_id(
		jd3::PrelimJobNodeID input_pose_id,
		jd3::NStructIndex nstruct_ind
	);

	std::vector< TagListOP > const & tag_list_for_input_pose_id() const {
		return tag_list_for_input_pose_id_;
	}

protected:
	std::vector< TagListOP > & tag_list_for_input_pose_id() {
		return tag_list_for_input_pose_id_;
	}

private:
	std::vector< TagListOP > tag_list_for_input_pose_id_;//[0] only holds common data

	///@brief cache the most recent request because it may get called again soon
	ParsedTagCacheOP most_recent_request_;

#ifdef    SERIALIZATION
public:
	template< class Archive > void save( Archive & arc ) const;
	template< class Archive > void load( Archive & arc );
#endif // SERIALIZATION

};

} //multistage_rosetta_scripts
} //protocols

#ifdef    SERIALIZATION
CEREAL_FORCE_DYNAMIC_INIT( protocols_multistage_rosetta_scripts_TagManager )
#endif // SERIALIZATION


#endif
