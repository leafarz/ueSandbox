// Fill out your copyright notice in the Description page of Project Settings.


#include "ReflectionHelper.h"
#include "ARFilter.h"
#include "AssetRegistryModule.h"
#include "Engine/Blueprint.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "Misc/PackageName.h"
#include "Templates/SubclassOf.h"

void UReflectionHelper::GetBlueprintsOfClass(TSubclassOf<UObject> Base,
	FString Path,
	TArray<TAssetSubclassOf<UObject>>& Subclasses,
	const TArray<FString>& OtherContentPaths)
{
	// Load the asset registry module
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	// The asset registry is populated asynchronously at startup, so there's no guarantee it has finished.
	// This simple approach just runs a synchronous scan on the entire content directory.
	// Better solutions would be to specify only the path to where the relevant blueprints are,
	// or to register a callback with the asset registry to be notified of when it's finished populating.
	TArray<FString> ContentPaths;
	ContentPaths.Add(TEXT("/Game"));

	for (const auto& ContentPath : OtherContentPaths)
	{
		FString ParsedContentPath = ContentPath.TrimStartAndEnd();
		if (ParsedContentPath.IsEmpty())
		{
			continue;
		}

		if (!ParsedContentPath.StartsWith("/"))
		{
			ParsedContentPath = "/" + ParsedContentPath;
		}

		ContentPaths.AddUnique(ParsedContentPath);
	}

	AssetRegistry.ScanPathsSynchronous(ContentPaths);

	FName BaseClassName = Base->GetFName();

	// Use the asset registry to get the set of all class names deriving from Base
	TSet<FName> DerivedNames;
	{
		TArray<FName> BaseNames;
		BaseNames.Add(BaseClassName);

		TSet<FName> Excluded;
		AssetRegistry.GetDerivedClassNames(BaseNames, Excluded, DerivedNames);
	}

	FARFilter Filter;
	Filter.ClassNames.Add(UBlueprint::StaticClass()->GetFName());
	Filter.bRecursiveClasses = true;
	if (!Path.IsEmpty())
	{
		Filter.PackagePaths.Add(*Path);
	}
	Filter.bRecursivePaths = true;

	TArray<FAssetData> AssetList;
	AssetRegistry.GetAssets(Filter, AssetList);

	// Iterate over retrieved blueprint assets
	for (auto const& Asset : AssetList)
	{
		// Get the the class this blueprint generates (this is stored as a full path)
		FAssetTagValueRef GeneratedClassPathPtr = Asset.TagsAndValues.FindTag(TEXT("GeneratedClass"));
		if (GeneratedClassPathPtr.IsSet())
		{
			FString GetGeneratedClassPathStr = GeneratedClassPathPtr.AsString();
			
			// Convert path to just the name part
			const FString ClassObjectPath = FPackageName::ExportTextPathToObjectPath(*GetGeneratedClassPathStr);
			const FString ClassName = FPackageName::ObjectPathToObjectName(ClassObjectPath);

			// Check if this class is in the derived set
			if (!DerivedNames.Contains(*ClassName))
			{
				continue;
			}

			// Store using the path to the generated class
			Subclasses.Add(TAssetSubclassOf<UObject>(FStringAssetReference(ClassObjectPath)));
		}
	}
}


FString UReflectionHelper::GetActorClassPath(AActor* Actor)
{
	return Actor->GetClass()->GetPathName();
}

UStaticMesh* UReflectionHelper::GetStaticMeshFromPath(FString Path)
{
	return Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *Path));
}

UMaterial* UReflectionHelper::GetMaterialByPath(FString Path)
{
	return Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, *Path));
}
