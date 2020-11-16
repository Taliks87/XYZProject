// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef XYZPROJECT_BasePlatform_generated_h
#error "BasePlatform.generated.h already included, missing '#pragma once' in BasePlatform.h"
#endif
#define XYZPROJECT_BasePlatform_generated_h

#define XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_25_DELEGATE \
static inline void FOnPlatformMoved_DelegateWrapper(const FMulticastScriptDelegate& OnPlatformMoved) \
{ \
	OnPlatformMoved.ProcessMulticastDelegate<UObject>(NULL); \
}


#define XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_SPARSE_DATA
#define XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execStartTimerDelayMovement); \
	DECLARE_FUNCTION(execUpdatePlatformMove); \
	DECLARE_FUNCTION(execMovePlatform);


#define XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execStartTimerDelayMovement); \
	DECLARE_FUNCTION(execUpdatePlatformMove); \
	DECLARE_FUNCTION(execMovePlatform);


#define XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesABasePlatform(); \
	friend struct Z_Construct_UClass_ABasePlatform_Statics; \
public: \
	DECLARE_CLASS(ABasePlatform, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/XYZProject"), NO_API) \
	DECLARE_SERIALIZER(ABasePlatform)


#define XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_INCLASS \
private: \
	static void StaticRegisterNativesABasePlatform(); \
	friend struct Z_Construct_UClass_ABasePlatform_Statics; \
public: \
	DECLARE_CLASS(ABasePlatform, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/XYZProject"), NO_API) \
	DECLARE_SERIALIZER(ABasePlatform)


#define XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ABasePlatform(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ABasePlatform) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABasePlatform); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABasePlatform); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ABasePlatform(ABasePlatform&&); \
	NO_API ABasePlatform(const ABasePlatform&); \
public:


#define XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ABasePlatform(ABasePlatform&&); \
	NO_API ABasePlatform(const ABasePlatform&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABasePlatform); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABasePlatform); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ABasePlatform)


#define XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__PlatformMeshComponent() { return STRUCT_OFFSET(ABasePlatform, PlatformMeshComponent); } \
	FORCEINLINE static uint32 __PPO__EndLocation() { return STRUCT_OFFSET(ABasePlatform, EndLocation); } \
	FORCEINLINE static uint32 __PPO__StartLocation() { return STRUCT_OFFSET(ABasePlatform, StartLocation); } \
	FORCEINLINE static uint32 __PPO__PlatformBehavior() { return STRUCT_OFFSET(ABasePlatform, PlatformBehavior); } \
	FORCEINLINE static uint32 __PPO__MotionCurve() { return STRUCT_OFFSET(ABasePlatform, MotionCurve); } \
	FORCEINLINE static uint32 __PPO__ForwardMovingRate() { return STRUCT_OFFSET(ABasePlatform, ForwardMovingRate); } \
	FORCEINLINE static uint32 __PPO__BackwardMovingRate() { return STRUCT_OFFSET(ABasePlatform, BackwardMovingRate); } \
	FORCEINLINE static uint32 __PPO__OnPlatformMoved() { return STRUCT_OFFSET(ABasePlatform, OnPlatformMoved); } \
	FORCEINLINE static uint32 __PPO__MotionDelay() { return STRUCT_OFFSET(ABasePlatform, MotionDelay); }


#define XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_27_PROLOG
#define XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_PRIVATE_PROPERTY_OFFSET \
	XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_SPARSE_DATA \
	XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_RPC_WRAPPERS \
	XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_INCLASS \
	XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_PRIVATE_PROPERTY_OFFSET \
	XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_SPARSE_DATA \
	XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_RPC_WRAPPERS_NO_PURE_DECLS \
	XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_INCLASS_NO_PURE_DECLS \
	XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h_30_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> XYZPROJECT_API UClass* StaticClass<class ABasePlatform>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID XYZProject_Source_XYZProject_Placeables_Platform_BasePlatform_h


#define FOREACH_ENUM_EPLATFORMMOVEDIRECTION(op) \
	op(EPlatformMoveDirection::Anywhere) \
	op(EPlatformMoveDirection::Forward) \
	op(EPlatformMoveDirection::Backward) 

enum class EPlatformMoveDirection : uint8;
template<> XYZPROJECT_API UEnum* StaticEnum<EPlatformMoveDirection>();

#define FOREACH_ENUM_EPLATFORMBEHAVIOR(op) \
	op(EPlatformBehavior::OnDemand) \
	op(EPlatformBehavior::Loop) 

enum class EPlatformBehavior : uint8;
template<> XYZPROJECT_API UEnum* StaticEnum<EPlatformBehavior>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
