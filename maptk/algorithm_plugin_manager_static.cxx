/*ckwg +29
 * Copyright 2015 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file
 * \brief Definition of static-build plugin algorithm registration function
 */

#ifndef MAPTK_PLUGIN_INTERFACE_STATIC_REGISTRATION_INTERFACE_H
#define MAPTK_PLUGIN_INTERFACE_STATIC_REGISTRATION_INTERFACE_H

#include "algorithm_plugin_manager_static.h"

#include <maptk/config.h>
#include <maptk/logging_macros.h>


// Include Plugins regustration function headers if static and enabled
#ifndef BUILD_SHARED_LIBS
# include <maptk/plugins/core/register_algorithms.h>
# if MAPTK_ENABLE_OPENCV
#   include <maptk/plugins/ocv/register_algorithms.h>
# endif
# if MAPTK_ENABLE_PROJ
#   include <maptk/plugins/proj/register_algorithms.h>
# endif
# if MAPTK_ENABLE_VISCL
#   include <maptk/plugins/viscl/register_algorithms.h>
# endif
# if MAPTK_ENABLE_VXL
#   include <maptk/plugins/vxl/register_algorithms.h>
# endif
#endif // ndef BUILD_SHARED_LIBS


namespace maptk
{

void static_register_algorithms()
{
  // Only give this function content if we are building statically
#ifndef BUILD_SHARED_LIBS
  static const char* logging_prefix = "maptk::static_register_algorithms";
  int tmp;

# define register_module(name) \
  tmp = name::register_algorithms( registrar::instance() ); \
  if( tmp ) \
  { \
    LOG_WARN( logging_prefix, \
              tmp << " algorithms failed to register from module " \
              << "maptk::" << #name ); \
  }

  register_module( core );

# if MAPTK_ENABLE_OPENCV
  register_module( ocv );
# endif

# if MAPTK_ENABLE_PROJ
  register_module( proj );
# endif

# if MAPTK_ENABLE_VISCL
  register_module( vcl );
# endif

# if MAPTK_ENABLE_VXL
  register_module( vxl );
# endif

# undef register_module

#endif // ndef BUILD_SHARED_LIBS
}

}


#endif // MAPTK_PLUGIN_INTERFACE_STATIC_REGISTRATION_INTERFACE_H
