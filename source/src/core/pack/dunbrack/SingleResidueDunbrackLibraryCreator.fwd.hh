// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file   core/pack/dunbrack/SingleResidueDunbrackLibraryCreator.fwd.hh
/// @brief  Forward declaration of a class that instantiates a particular SingleResidueDunbrackLibrary
/// @author Rocco Moretti (rmorettiase@gmail.com)

#ifndef INCLUDED_core_pack_dunbrack_SingleResidueDunbrackLibraryCreator_FWD_HH
#define INCLUDED_core_pack_dunbrack_SingleResidueDunbrackLibraryCreator_FWD_HH

// Utility Headers
#include <utility/pointer/owning_ptr.hh>

namespace core {
namespace pack {
namespace dunbrack {

class SingleResidueDunbrackLibraryCreator;

typedef utility::pointer::shared_ptr< SingleResidueDunbrackLibraryCreator > SingleResidueDunbrackLibraryCreatorOP;
typedef utility::pointer::shared_ptr< SingleResidueDunbrackLibraryCreator const > SingleResidueDunbrackLibraryCreatorCOP;


} //namespace dunbrack
} //namespace pack
} //namespace core


#endif
