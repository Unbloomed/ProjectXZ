#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STableRow.h"

struct FWeaponRowData
{
	int Number;
	FString Name;
	class UXZDA_Weapon* Asset;

	FWeaponRowData() { }
	FWeaponRowData(int32 InNumber, FString InName, class UXZDA_Weapon* InAsset)
		: Number(InNumber), Name(InName), Asset(InAsset) {	}

	static TSharedPtr<FWeaponRowData> Make(int32 InNumber, FString InName, class UXZDA_Weapon* InAsset)
	{
		return MakeShareable(new FWeaponRowData(InNumber, InName, InAsset));
	}
};
typedef TSharedPtr<FWeaponRowData> FWeaponRowDataPtr; // 실제 출력할 자료형


class WEAPONPLUGIN_API XZWeaponTableRow : public SMultiColumnTableRow<FWeaponRowDataPtr>
{
public:
	SLATE_BEGIN_ARGS(XZWeaponTableRow) {}
	SLATE_ARGUMENT(FWeaponRowDataPtr, RowData)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable);

protected:
	TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;

private:
	FWeaponRowDataPtr Data;
};

/** Slate UI 창의 왼쪽 부분을 담당하는 클래스
 * 
 */
class WEAPONPLUGIN_API XZWeaponLeftArea : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(XZWeaponLeftArea) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	TSharedRef<ITableRow> OnGenerateRow(FWeaponRowDataPtr InRow, const TSharedRef<STableViewBase>& InTable);

	FText OnGetAssetCount() const;

	void ReadDataAssetList();

	TArray<FWeaponRowDataPtr> RowDatas;
	TSharedPtr<SListView<FWeaponRowDataPtr>> ListView;
};
