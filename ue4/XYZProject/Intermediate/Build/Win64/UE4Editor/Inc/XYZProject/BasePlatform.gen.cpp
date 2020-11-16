// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "XYZProject/Placeables/Platform/BasePlatform.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBasePlatform() {}
// Cross Module References
	XYZPROJECT_API UFunction* Z_Construct_UDelegateFunction_XYZProject_OnPlatformMoved__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_XYZProject();
	XYZPROJECT_API UEnum* Z_Construct_UEnum_XYZProject_EPlatformMoveDirection();
	XYZPROJECT_API UEnum* Z_Construct_UEnum_XYZProject_EPlatformBehavior();
	XYZPROJECT_API UClass* Z_Construct_UClass_ABasePlatform_NoRegister();
	XYZPROJECT_API UClass* Z_Construct_UClass_ABasePlatform();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_UCurveFloat_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_XYZProject_OnPlatformMoved__DelegateSignature_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_XYZProject_OnPlatformMoved__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_XYZProject_OnPlatformMoved__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_XYZProject, nullptr, "OnPlatformMoved__DelegateSignature", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_XYZProject_OnPlatformMoved__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_XYZProject_OnPlatformMoved__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_XYZProject_OnPlatformMoved__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_XYZProject_OnPlatformMoved__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	static UEnum* EPlatformMoveDirection_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_XYZProject_EPlatformMoveDirection, Z_Construct_UPackage__Script_XYZProject(), TEXT("EPlatformMoveDirection"));
		}
		return Singleton;
	}
	template<> XYZPROJECT_API UEnum* StaticEnum<EPlatformMoveDirection>()
	{
		return EPlatformMoveDirection_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EPlatformMoveDirection(EPlatformMoveDirection_StaticEnum, TEXT("/Script/XYZProject"), TEXT("EPlatformMoveDirection"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_XYZProject_EPlatformMoveDirection_Hash() { return 175121811U; }
	UEnum* Z_Construct_UEnum_XYZProject_EPlatformMoveDirection()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_XYZProject();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EPlatformMoveDirection"), 0, Get_Z_Construct_UEnum_XYZProject_EPlatformMoveDirection_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EPlatformMoveDirection::Anywhere", (int64)EPlatformMoveDirection::Anywhere },
				{ "EPlatformMoveDirection::Forward", (int64)EPlatformMoveDirection::Forward },
				{ "EPlatformMoveDirection::Backward", (int64)EPlatformMoveDirection::Backward },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Anywhere.Name", "EPlatformMoveDirection::Anywhere" },
				{ "Backward.Name", "EPlatformMoveDirection::Backward" },
				{ "Forward.Name", "EPlatformMoveDirection::Forward" },
				{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_XYZProject,
				nullptr,
				"EPlatformMoveDirection",
				"EPlatformMoveDirection",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* EPlatformBehavior_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_XYZProject_EPlatformBehavior, Z_Construct_UPackage__Script_XYZProject(), TEXT("EPlatformBehavior"));
		}
		return Singleton;
	}
	template<> XYZPROJECT_API UEnum* StaticEnum<EPlatformBehavior>()
	{
		return EPlatformBehavior_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EPlatformBehavior(EPlatformBehavior_StaticEnum, TEXT("/Script/XYZProject"), TEXT("EPlatformBehavior"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_XYZProject_EPlatformBehavior_Hash() { return 3590452760U; }
	UEnum* Z_Construct_UEnum_XYZProject_EPlatformBehavior()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_XYZProject();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EPlatformBehavior"), 0, Get_Z_Construct_UEnum_XYZProject_EPlatformBehavior_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EPlatformBehavior::OnDemand", (int64)EPlatformBehavior::OnDemand },
				{ "EPlatformBehavior::Loop", (int64)EPlatformBehavior::Loop },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Loop.Name", "EPlatformBehavior::Loop" },
				{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
				{ "OnDemand.Name", "EPlatformBehavior::OnDemand" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_XYZProject,
				nullptr,
				"EPlatformBehavior",
				"EPlatformBehavior",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	DEFINE_FUNCTION(ABasePlatform::execStartTimerDelayMovement)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StartTimerDelayMovement();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ABasePlatform::execUpdatePlatformMove)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UpdatePlatformMove(Z_Param_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ABasePlatform::execMovePlatform)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->MovePlatform();
		P_NATIVE_END;
	}
	void ABasePlatform::StaticRegisterNativesABasePlatform()
	{
		UClass* Class = ABasePlatform::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "MovePlatform", &ABasePlatform::execMovePlatform },
			{ "StartTimerDelayMovement", &ABasePlatform::execStartTimerDelayMovement },
			{ "UpdatePlatformMove", &ABasePlatform::execUpdatePlatformMove },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ABasePlatform_MovePlatform_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ABasePlatform_MovePlatform_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ABasePlatform_MovePlatform_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ABasePlatform, nullptr, "MovePlatform", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ABasePlatform_MovePlatform_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ABasePlatform_MovePlatform_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ABasePlatform_MovePlatform()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ABasePlatform_MovePlatform_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ABasePlatform_StartTimerDelayMovement_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ABasePlatform_StartTimerDelayMovement_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ABasePlatform_StartTimerDelayMovement_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ABasePlatform, nullptr, "StartTimerDelayMovement", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ABasePlatform_StartTimerDelayMovement_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ABasePlatform_StartTimerDelayMovement_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ABasePlatform_StartTimerDelayMovement()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ABasePlatform_StartTimerDelayMovement_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ABasePlatform_UpdatePlatformMove_Statics
	{
		struct BasePlatform_eventUpdatePlatformMove_Parms
		{
			float Value;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ABasePlatform_UpdatePlatformMove_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BasePlatform_eventUpdatePlatformMove_Parms, Value), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ABasePlatform_UpdatePlatformMove_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ABasePlatform_UpdatePlatformMove_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ABasePlatform_UpdatePlatformMove_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ABasePlatform_UpdatePlatformMove_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ABasePlatform, nullptr, "UpdatePlatformMove", nullptr, nullptr, sizeof(BasePlatform_eventUpdatePlatformMove_Parms), Z_Construct_UFunction_ABasePlatform_UpdatePlatformMove_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ABasePlatform_UpdatePlatformMove_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ABasePlatform_UpdatePlatformMove_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ABasePlatform_UpdatePlatformMove_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ABasePlatform_UpdatePlatformMove()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ABasePlatform_UpdatePlatformMove_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ABasePlatform_NoRegister()
	{
		return ABasePlatform::StaticClass();
	}
	struct Z_Construct_UClass_ABasePlatform_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MotionDelay_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MotionDelay;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnPlatformMoved_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnPlatformMoved;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BackwardMovingRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_BackwardMovingRate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ForwardMovingRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ForwardMovingRate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MotionCurve_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_MotionCurve;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PlatformBehavior_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_PlatformBehavior;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_PlatformBehavior_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StartLocation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_StartLocation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EndLocation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_EndLocation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PlatformMeshComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_PlatformMeshComponent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABasePlatform_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_XYZProject,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ABasePlatform_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ABasePlatform_MovePlatform, "MovePlatform" }, // 247682801
		{ &Z_Construct_UFunction_ABasePlatform_StartTimerDelayMovement, "StartTimerDelayMovement" }, // 1642248553
		{ &Z_Construct_UFunction_ABasePlatform_UpdatePlatformMove, "UpdatePlatformMove" }, // 3447424193
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABasePlatform_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Placeables/Platform/BasePlatform.h" },
		{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABasePlatform_Statics::NewProp_MotionDelay_MetaData[] = {
		{ "Category", "Platform settings" },
		{ "ClampMin", "0.000000" },
		{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
		{ "UIMin", "0.000000" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABasePlatform_Statics::NewProp_MotionDelay = { "MotionDelay", nullptr, (EPropertyFlags)0x0020080000000015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABasePlatform, MotionDelay), METADATA_PARAMS(Z_Construct_UClass_ABasePlatform_Statics::NewProp_MotionDelay_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABasePlatform_Statics::NewProp_MotionDelay_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABasePlatform_Statics::NewProp_OnPlatformMoved_MetaData[] = {
		{ "Category", "Platform settings" },
		{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ABasePlatform_Statics::NewProp_OnPlatformMoved = { "OnPlatformMoved", nullptr, (EPropertyFlags)0x0020080010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABasePlatform, OnPlatformMoved), Z_Construct_UDelegateFunction_XYZProject_OnPlatformMoved__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_ABasePlatform_Statics::NewProp_OnPlatformMoved_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABasePlatform_Statics::NewProp_OnPlatformMoved_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABasePlatform_Statics::NewProp_BackwardMovingRate_MetaData[] = {
		{ "Category", "Platform settings" },
		{ "ClampMin", "0.000100" },
		{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
		{ "UIMin", "0.000100" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABasePlatform_Statics::NewProp_BackwardMovingRate = { "BackwardMovingRate", nullptr, (EPropertyFlags)0x0020080000000015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABasePlatform, BackwardMovingRate), METADATA_PARAMS(Z_Construct_UClass_ABasePlatform_Statics::NewProp_BackwardMovingRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABasePlatform_Statics::NewProp_BackwardMovingRate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABasePlatform_Statics::NewProp_ForwardMovingRate_MetaData[] = {
		{ "Category", "Platform settings" },
		{ "ClampMin", "0.000100" },
		{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
		{ "UIMin", "0.000100" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABasePlatform_Statics::NewProp_ForwardMovingRate = { "ForwardMovingRate", nullptr, (EPropertyFlags)0x0020080000000015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABasePlatform, ForwardMovingRate), METADATA_PARAMS(Z_Construct_UClass_ABasePlatform_Statics::NewProp_ForwardMovingRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABasePlatform_Statics::NewProp_ForwardMovingRate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABasePlatform_Statics::NewProp_MotionCurve_MetaData[] = {
		{ "Category", "Platform settings" },
		{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABasePlatform_Statics::NewProp_MotionCurve = { "MotionCurve", nullptr, (EPropertyFlags)0x0020080000000015, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABasePlatform, MotionCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ABasePlatform_Statics::NewProp_MotionCurve_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABasePlatform_Statics::NewProp_MotionCurve_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABasePlatform_Statics::NewProp_PlatformBehavior_MetaData[] = {
		{ "Category", "Platform settings" },
		{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_ABasePlatform_Statics::NewProp_PlatformBehavior = { "PlatformBehavior", nullptr, (EPropertyFlags)0x0020080000000015, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABasePlatform, PlatformBehavior), Z_Construct_UEnum_XYZProject_EPlatformBehavior, METADATA_PARAMS(Z_Construct_UClass_ABasePlatform_Statics::NewProp_PlatformBehavior_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABasePlatform_Statics::NewProp_PlatformBehavior_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_ABasePlatform_Statics::NewProp_PlatformBehavior_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABasePlatform_Statics::NewProp_StartLocation_MetaData[] = {
		{ "Category", "BasePlatform" },
		{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ABasePlatform_Statics::NewProp_StartLocation = { "StartLocation", nullptr, (EPropertyFlags)0x0020080000022015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABasePlatform, StartLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_ABasePlatform_Statics::NewProp_StartLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABasePlatform_Statics::NewProp_StartLocation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABasePlatform_Statics::NewProp_EndLocation_MetaData[] = {
		{ "Category", "Platform settings" },
		{ "MakeEditWidget", "" },
		{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ABasePlatform_Statics::NewProp_EndLocation = { "EndLocation", nullptr, (EPropertyFlags)0x0020080000000815, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABasePlatform, EndLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_ABasePlatform_Statics::NewProp_EndLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABasePlatform_Statics::NewProp_EndLocation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABasePlatform_Statics::NewProp_PlatformMeshComponent_MetaData[] = {
		{ "Category", "Platform settings" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Placeables/Platform/BasePlatform.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABasePlatform_Statics::NewProp_PlatformMeshComponent = { "PlatformMeshComponent", nullptr, (EPropertyFlags)0x002008000008001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ABasePlatform, PlatformMeshComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ABasePlatform_Statics::NewProp_PlatformMeshComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ABasePlatform_Statics::NewProp_PlatformMeshComponent_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABasePlatform_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABasePlatform_Statics::NewProp_MotionDelay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABasePlatform_Statics::NewProp_OnPlatformMoved,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABasePlatform_Statics::NewProp_BackwardMovingRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABasePlatform_Statics::NewProp_ForwardMovingRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABasePlatform_Statics::NewProp_MotionCurve,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABasePlatform_Statics::NewProp_PlatformBehavior,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABasePlatform_Statics::NewProp_PlatformBehavior_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABasePlatform_Statics::NewProp_StartLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABasePlatform_Statics::NewProp_EndLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABasePlatform_Statics::NewProp_PlatformMeshComponent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABasePlatform_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABasePlatform>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ABasePlatform_Statics::ClassParams = {
		&ABasePlatform::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ABasePlatform_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ABasePlatform_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ABasePlatform_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ABasePlatform_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ABasePlatform()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ABasePlatform_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ABasePlatform, 1537172794);
	template<> XYZPROJECT_API UClass* StaticClass<ABasePlatform>()
	{
		return ABasePlatform::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ABasePlatform(Z_Construct_UClass_ABasePlatform, &ABasePlatform::StaticClass, TEXT("/Script/XYZProject"), TEXT("ABasePlatform"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABasePlatform);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
