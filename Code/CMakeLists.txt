
# Currently we are in the Code folder: ${CMAKE_CURRENT_LIST_DIR}
# Get the platform specific folder ${pal_dir} for the current folder: ${CMAKE_CURRENT_LIST_DIR}/Platform/${PAL_PLATFORM_NAME}
# Note: o3de_pal_dir will take care of the details for us, as this may be a restricted platform
#       in which case it will see if that platform is present here or in the restricted folder.
#       i.e. It could here in our gem : Gems/O3deUtils_Misc/Code/Platform/<platorm_name>  or
#            <restricted_folder>/<platform_name>/Gems/O3deUtils_Misc/Code
o3de_pal_dir(pal_dir ${CMAKE_CURRENT_LIST_DIR}/Platform/${PAL_PLATFORM_NAME} "${gem_restricted_path}" "${gem_path}" "${gem_parent_relative_path}")

# Now that we have the platform abstraction layer (PAL) folder for this folder, thats where we will find the
# traits for this platform. Traits for a platform are defines for things like whether or not something in this gem
# is supported by this platform.
include(${pal_dir}/PAL_${PAL_PLATFORM_NAME_LOWERCASE}.cmake)

# Check to see if building the Gem Modules are supported for the current platform
if(NOT PAL_TRAIT_O3DEUTILS_MISC_SUPPORTED)
    return()
endif()

# Define common data used by all unified, server, and client versions of our ".API" target.

set(${gem_name}_COMMON_API_FILES_CMAKE
    o3deutils_misc_api_files.cmake
    ${pal_dir}/o3deutils_misc_api_files.cmake
)

ly_add_target(
    NAME ${gem_name}.Common.API INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_API_FILES_CMAKE}
    INCLUDE_DIRECTORIES
        INTERFACE
            Include
    BUILD_DEPENDENCIES
        INTERFACE
            AZ::AzCore
)

# Add our actual ".API" targets.

ly_add_target(
    NAME ${gem_name}.API INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_API_FILES_CMAKE}
    BUILD_DEPENDENCIES
        INTERFACE
            Gem::${gem_name}.Common.API
)

ly_add_target(
    NAME ${gem_name}.Server.API INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_API_FILES_CMAKE}
    BUILD_DEPENDENCIES
        INTERFACE
            Gem::${gem_name}.Common.API
)

ly_add_target(
    NAME ${gem_name}.Client.API INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_API_FILES_CMAKE}
    BUILD_DEPENDENCIES
        INTERFACE
            Gem::${gem_name}.Common.API
)

# Define common data used by all unified, server, and client versions of our ".Private.Object" target.

set(${gem_name}_COMMON_PRIVATE_OBJECT_FILES_CMAKE
    o3deutils_misc_private_files.cmake
    ${pal_dir}/o3deutils_misc_private_files.cmake
)

set(${gem_name}_COMMON_PRIVATE_OBJECT_TARGET_PROPERTIES
    O3DE_PRIVATE_TARGET TRUE
)

ly_add_target(
    NAME ${gem_name}.Common.Private.Object INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_PRIVATE_OBJECT_FILES_CMAKE}
    COMPILE_DEFINITIONS
        INTERFACE
            O3DEUTILS_MISC_EXPORTS
    TARGET_PROPERTIES
        ${${gem_name}_COMMON_PRIVATE_OBJECT_TARGET_PROPERTIES}
    INCLUDE_DIRECTORIES
        INTERFACE
            .
    BUILD_DEPENDENCIES
        INTERFACE
            AZ::AzCore
            AZ::AzFramework
            Legacy::CryCommon
)

# Add our ".Private.Object" targets. @Christian: TODO: [todo][techdebt][cmake][multiplayer] Support multiplayer compile definitions (`AZ_TRAIT_CLIENT` and `AZ_TRAIT_SERVER`) without needing to depend on the multiplayer gem?

ly_add_target(
    NAME ${gem_name}.Unified.Private.Object INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_PRIVATE_OBJECT_FILES_CMAKE}
    TARGET_PROPERTIES
        ${${gem_name}_COMMON_PRIVATE_OBJECT_TARGET_PROPERTIES}
    BUILD_DEPENDENCIES
        INTERFACE
            Gem::${gem_name}.Common.Private.Object
            Gem::${gem_name}.API
)

ly_add_target(
    NAME ${gem_name}.Server.Private.Object INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_PRIVATE_OBJECT_FILES_CMAKE}
    TARGET_PROPERTIES
        ${${gem_name}_COMMON_PRIVATE_OBJECT_TARGET_PROPERTIES}
    BUILD_DEPENDENCIES
        INTERFACE
            Gem::${gem_name}.Common.Private.Object
            Gem::${gem_name}.Server.API
)

ly_add_target(
    NAME ${gem_name}.Client.Private.Object INTERFACE
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_PRIVATE_OBJECT_FILES_CMAKE}
    TARGET_PROPERTIES
        ${${gem_name}_COMMON_PRIVATE_OBJECT_TARGET_PROPERTIES}
    BUILD_DEPENDENCIES
        INTERFACE
            Gem::${gem_name}.Common.Private.Object
            Gem::${gem_name}.Client.API
)

# Define common data used by all unified, server, and client versions of our main gem target.

set(${gem_name}_COMMON_FILES_CMAKE
    ${${gem_name}_COMMON_API_FILES_CMAKE}
    ${${gem_name}_COMMON_PRIVATE_OBJECT_FILES_CMAKE}
    o3deutils_misc_shared_files.cmake
    ${pal_dir}/o3deutils_misc_shared_files.cmake
)

# Add our main gem targets. These depend on their corresponding ".Private.Object" and ".API" targets.

ly_add_target(
    NAME ${gem_name} ${PAL_TRAIT_MONOLITHIC_DRIVEN_LIBRARY_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_FILES_CMAKE}
    BUILD_DEPENDENCIES
        PUBLIC
            Gem::${gem_name}.API
        PRIVATE
            Gem::${gem_name}.Unified.Private.Object
)

ly_add_target(
    NAME ${gem_name}.Server ${PAL_TRAIT_MONOLITHIC_DRIVEN_LIBRARY_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_FILES_CMAKE}
    BUILD_DEPENDENCIES
        PUBLIC
            Gem::${gem_name}.Server.API
        PRIVATE
            Gem::${gem_name}.Server.Private.Object
)

ly_add_target(
    NAME ${gem_name}.Client ${PAL_TRAIT_MONOLITHIC_DRIVEN_LIBRARY_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        ${${gem_name}_COMMON_FILES_CMAKE}
    BUILD_DEPENDENCIES
        PUBLIC
            Gem::${gem_name}.Client.API
        PRIVATE
            Gem::${gem_name}.Client.Private.Object
)

# Unset these variables, as they are no longer needed.
unset(${gem_name}_COMMON_API_FILES_CMAKE)

# Unset these variables, as they are no longer needed.
unset(${gem_name}_COMMON_PRIVATE_OBJECT_FILES_CMAKE)
unset(${gem_name}_COMMON_PRIVATE_OBJECT_TARGET_PROPERTIES)

# Unset these variables, as they are no longer needed.
unset(${gem_name}_COMMON_FILES_CMAKE)

# Include the gem name into the Client Module source file
# for use with the AZ_DECLARE_MODULE_CLASS macro
# This is to allow renaming of the gem to also cause
# the CreateModuleClass_Gem_<gem-name> function which
# is used to bootstrap the gem in monolithic builds to link to the new gem name
ly_add_source_properties(
SOURCES
    Source/O3deUtils_MiscModule.cpp
PROPERTY COMPILE_DEFINITIONS
    VALUES
        O3DE_GEM_NAME=${gem_name}
        O3DE_GEM_VERSION=${gem_version})

# By default, we will specify that the above target ${gem_name} would be used by
# Client and Server type targets when this gem is enabled.  If you don't want it
# active in Clients or Servers by default, delete one of both of the following lines:
ly_create_alias(NAME ${gem_name}.Unified NAMESPACE Gem TARGETS Gem::${gem_name})
ly_create_alias(NAME ${gem_name}.Servers NAMESPACE Gem TARGETS Gem::${gem_name}.Server)
ly_create_alias(NAME ${gem_name}.Clients NAMESPACE Gem TARGETS Gem::${gem_name}.Client)

# For the Client and Server variants of ${gem_name} Gem, an alias to the ".API" target will be made
ly_create_alias(NAME ${gem_name}.Unified.API NAMESPACE Gem TARGETS Gem::${gem_name}.API)
ly_create_alias(NAME ${gem_name}.Servers.API NAMESPACE Gem TARGETS Gem::${gem_name}.Server.API)
ly_create_alias(NAME ${gem_name}.Clients.API NAMESPACE Gem TARGETS Gem::${gem_name}.Client.API)

# Add in CMake dependencies for each gem dependency listed in this gem's gem.json file
# for the Clients, Servers, Unified gem variants
o3de_add_variant_dependencies_for_gem_dependencies(GEM_NAME ${gem_name} VARIANTS Clients Servers Unified)

# If we are on a host platform, we want to add the host tools targets like the ${gem_name}.Editor MODULE target
if(PAL_TRAIT_BUILD_HOST_TOOLS)
    # The ${gem_name}.Editor.API target can be used by other gems that want to interact with the ${gem_name}.Editor module
    ly_add_target(
        NAME ${gem_name}.Editor.API INTERFACE
        NAMESPACE Gem
        FILES_CMAKE
            o3deutils_misc_editor_api_files.cmake
            ${pal_dir}/o3deutils_misc_editor_api_files.cmake
        INCLUDE_DIRECTORIES
            INTERFACE
                Include
        BUILD_DEPENDENCIES
            INTERFACE
                AZ::AzToolsFramework
    )

    # The ${gem_name}.Editor.Private.Object target is an internal target
    # which is only to be used by this gems CMakeLists.txt and any subdirectories
    # Other gems should not use this target
    ly_add_target(
        NAME ${gem_name}.Editor.Private.Object STATIC
        NAMESPACE Gem
        FILES_CMAKE
            o3deutils_misc_editor_private_files.cmake
        TARGET_PROPERTIES
            O3DE_PRIVATE_TARGET TRUE
        INCLUDE_DIRECTORIES
            PRIVATE
                Include
                .
        BUILD_DEPENDENCIES
            PUBLIC
                AZ::AzToolsFramework
                ${gem_name}.Unified.Private.Object
    )

    ly_add_target(
        NAME ${gem_name}.Editor GEM_MODULE
        NAMESPACE Gem
        AUTOMOC
        FILES_CMAKE
            o3deutils_misc_editor_shared_files.cmake
        COMPILE_DEFINITIONS
            PRIVATE
                O3DEUTILS_MISC_EXPORTS
        INCLUDE_DIRECTORIES
            PRIVATE
                .
            PUBLIC
                Include
        BUILD_DEPENDENCIES
            PUBLIC
                Gem::${gem_name}.Editor.API
            PRIVATE
                Gem::${gem_name}.Editor.Private.Object
    )

    # Include the gem name into the Editor Module source file
    # for use with the AZ_DECLARE_MODULE_CLASS macro
    # This is to allow renaming of the gem to also cause
    # the CreateModuleClass_Gem_<gem-name> function which
    # is used to bootstrap the gem in monolithic builds to link to the new gem name
    ly_add_source_properties(
    SOURCES
        Source/Tools/O3deUtils_MiscEditorModule.cpp
    PROPERTY COMPILE_DEFINITIONS
        VALUES
            O3DE_GEM_NAME=${gem_name}
            O3DE_GEM_VERSION=${gem_version})

    # By default, we will specify that the above target ${gem_name} would be used by
    # Tool and Builder type targets when this gem is enabled.  If you don't want it
    # active in Tools or Builders by default, delete one of both of the following lines:
    ly_create_alias(NAME ${gem_name}.Tools    NAMESPACE Gem TARGETS Gem::${gem_name}.Editor)
    ly_create_alias(NAME ${gem_name}.Builders NAMESPACE Gem TARGETS Gem::${gem_name}.Editor)

    # For the Tools and Builders variants of ${gem_name} Gem, an alias to the ${gem_name}.Editor API target will be made
    ly_create_alias(NAME ${gem_name}.Tools.API NAMESPACE Gem TARGETS Gem::${gem_name}.Editor.API)
    ly_create_alias(NAME ${gem_name}.Builders.API NAMESPACE Gem TARGETS Gem::${gem_name}.Editor.API)

    # Add in CMake dependencies for each gem dependency listed in this gem's gem.json file
    # for the Tools and Builders gem variants
    o3de_add_variant_dependencies_for_gem_dependencies(GEM_NAME ${gem_name} VARIANTS Tools Builders)
endif()

################################################################################
# Tests
################################################################################
# See if globally, tests are supported
if(PAL_TRAIT_BUILD_TESTS_SUPPORTED)
    # We globally support tests, see if we support tests on this platform for ${gem_name}.Tests
    if(PAL_TRAIT_O3DEUTILS_MISC_TEST_SUPPORTED)
        # We support ${gem_name}.Tests on this platform, add dependency on the ".Private.Object" target
        ly_add_target(
            NAME ${gem_name}.Tests ${PAL_TRAIT_TEST_TARGET_TYPE}
            NAMESPACE Gem
            FILES_CMAKE
                o3deutils_misc_tests_files.cmake
            INCLUDE_DIRECTORIES
                PRIVATE
                    Tests
                    .
                    Include
            BUILD_DEPENDENCIES
                PRIVATE
                    AZ::AzTest
                    AZ::AzFramework
                    Gem::${gem_name}.Unified.Private.Object
        )

        # Add ${gem_name}.Tests to googletest
        ly_add_googletest(
            NAME Gem::${gem_name}.Tests
        )
    endif()

    # If we are a host platform we want to add tools test like editor tests here
    if(PAL_TRAIT_BUILD_HOST_TOOLS)
        # We are a host platform, see if Editor tests are supported on this platform
        if(PAL_TRAIT_O3DEUTILS_MISC_EDITOR_TEST_SUPPORTED)
            # We support ${gem_name}.Editor.Tests on this platform, add ${gem_name}.Editor.Tests target which depends on
            # private ${gem_name}.Editor.Private.Object target
            ly_add_target(
                NAME ${gem_name}.Editor.Tests ${PAL_TRAIT_TEST_TARGET_TYPE}
                NAMESPACE Gem
                FILES_CMAKE
                    o3deutils_misc_editor_tests_files.cmake
                INCLUDE_DIRECTORIES
                    PRIVATE
                        Tests
                        .
                        Include
                BUILD_DEPENDENCIES
                    PRIVATE
                        AZ::AzTest
                        Gem::${gem_name}.Editor.Private.Object
            )

            # Add ${gem_name}.Editor.Tests to googletest
            ly_add_googletest(
                NAME Gem::${gem_name}.Editor.Tests
            )
        endif()
    endif()
endif()
