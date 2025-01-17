// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file /src/apps/ncaa_utilities/MakeRotLib.cc
/// @brief MakeRotLib application
/// @author P. Douglas Renfrew ( renfrew@nyu.edu )

// unit headers
#include <protocols/make_rot_lib/MakeRotLibMover.hh>

// protocols header
#include <protocols/jd2/JobDistributor.hh>
#include <protocols/jd2/NoOutputJobOutputter.hh>

// devel headers
#include <devel/init.hh>

// basic headers
#include <basic/options/option.hh>
#include <basic/options/keys/make_rot_lib.OptionKeys.gen.hh>
#include <basic/Tracer.hh>

// utility headers
#include <utility/pointer/memory.hh>
#include <utility/excn/Exceptions.hh>

#include <protocols/make_rot_lib/RotData.hh> // MANUAL IWYU

static basic::Tracer TR( "MakeRotLib" );

int
main( int argc, char * argv [] )
{
	try {

		devel::init( argc, argv );

		protocols::make_rot_lib::MakeRotLibMoverOP mrlm( utility::pointer::make_shared< protocols::make_rot_lib::MakeRotLibMover >( basic::options::option[basic::options::OptionKeys::make_rot_lib::output_logging].value() ) );
		protocols::jd2::JobOutputterOP nojo( utility::pointer::make_shared< protocols::jd2::NoOutputJobOutputter >() );
		protocols::jd2::JobDistributor::get_instance()->go( mrlm, nojo );

		TR << "\n+-----------------------------------------------------------------+\n"
			<<   "|                              DONE                               |\n"
			<<   "+-----------------------------------------------------------------+" << std::endl;

	} catch (utility::excn::Exception const & e ) {
		e.display();
		return -1;
	}
	return 0;
}
