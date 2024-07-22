#include "AssetEditor/XZWeaponLeftArea.h"
#include "EditorStyleSet.h"
#include "EngineUtils.h"
#include "ProjectXZ/Weapon/XZDA_Weapon.h"
#include "Widgets/Input/SSearchBox.h"

void XZWeaponTableRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable)
{
	Data = InArgs._RowData;//InArgs를 통해서 들어온다.

	SMultiColumnTableRow<FWeaponRowDataPtr>::Construct
	(
		FSuperRowType::FArguments().Style(FAppStyle::Get(), "TableView.DarkRow"), InOwnerTable
	);
}

TSharedRef<SWidget> XZWeaponTableRow::GenerateWidgetForColumn(const FName& InColumnName)
{
	// InColumnName에 아래 Construct 내부의 SHeaderRow::Column("이름, 번호 등")이 들어간다.
	FString Str;
	if (InColumnName == "Number") // 숫자
	{
		Str = FString::FromInt(Data->Number); //str에 숫자를 넣어준다.
	}
	else if (InColumnName == "Name") // 이름
	{
		Str = Data->Name; // Str에 이름을 넣어준다.
	}

	return SNew(STextBlock)
		.Text(FText::FromString(Str)); // 출력할 문자str를 생성하여 리턴.
}

void XZWeaponLeftArea::Construct(const FArguments& InArgs)
{
	WeaponListViewSelectedItemDelegate = InArgs._WeaponSelectedItem;

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
			.AutoHeight().Padding(2, 0)
			[
				SAssignNew(SearchBox, SSearchBox) // SearchBox 동적할당
					.SelectAllTextWhenFocused(true)
					.OnTextChanged(this, &XZWeaponLeftArea::OnTextChanged)
					.OnTextCommitted(this, &XZWeaponLeftArea::OnTextCommitted)
			]
		+ SVerticalBox::Slot()
			.FillHeight(1) // 1은 100%를 의미(=한줄을 다 채우겠다는 의미)
			[
				SAssignNew(ListView, SListView<FWeaponRowDataPtr>) // ListView 동적할당. 자료형은 FWeaponRowDataPtr
					.HeaderRow
					(
						SNew(SHeaderRow)
						+ SHeaderRow::Column("Number")
							.DefaultLabel(FText::FromString(""))
							.ManualWidth(40) // 칸의 너비
						+ SHeaderRow::Column("Name")
							.DefaultLabel(FText::FromString("Name"))
					)
					.ListItemsSource(&RowDatas)
					.OnGenerateRow(this, &XZWeaponLeftArea::OnGenerateRow) // 한줄한줄 어떻게 표현할지 모양을 정해달라는 의미.
					.OnSelectionChanged(this, &XZWeaponLeftArea::OnSelectedChanged)
			]
		+ SVerticalBox::Slot()
			.AutoHeight()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Right)
			.Padding(FMargin(8, 2))
			[
				SNew(STextBlock)
					.Text(this, &XZWeaponLeftArea::OnGetAssetCount) // const TAttribute<FText>. 여기의 text 내용이 바뀌면 자동으로 갱신해준다. Attribute의 특성 때문이다. Attribute를 함수로 줄 수 있다. 여기서는 &SWeaponLeftArea::OnGetAssetCount.
			]
	];

	ReadDataAssetList();
}

void XZWeaponLeftArea::SelectedDataAsset(UXZDA_Weapon* InDA_Weapon)
{
	if (RowDatas.Num() <= 0) return; // XZDA_Weapon가 하나도 없는 경우 return

	for (FWeaponRowDataPtr RowData : RowDatas)
	{
		if (RowData->DA_Weapon == InDA_Weapon)
		{
			ListView->SetSelection(RowData);
			return;
		}
	}
}

TSharedRef<ITableRow> XZWeaponLeftArea::OnGenerateRow(FWeaponRowDataPtr InRow, const TSharedRef<STableViewBase>& InTable)
{
	/*실제모양을 만들어 리턴*/
	return SNew(XZWeaponTableRow, InTable)
		.RowData(InRow);
}

void XZWeaponLeftArea::ReadDataAssetList()
{
	RowDatas.Empty();//데이터를 불러오기 전에 비워주고 시작.

	// TODO: 경로 범위 좁히기
	// "/Game"은 콘텐츠 폴더. BP폴더 이하의 모든 에셋들을 찾아 objects에 리턴하겠다.
	// ATL_Class는 클래스 타입, ATL_Regular는 나머지 타입(에셋을 불러와야 하므로 이것 사용).
	TArray<UObject*> Objects;
	EngineUtils::FindOrLoadAssetsByPath("/Game/BP/", Objects, EngineUtils::ATL_Regular);

	int32 Idx = 0;
	for (UObject* obj : Objects)
	{
		UXZDA_Weapon* XZDA_Weapon = Cast<UXZDA_Weapon>(obj);
		if (false == IsValid(XZDA_Weapon)) continue;

		FString DataAssetName = XZDA_Weapon->GetName();
		if (false == SearchText.IsEmpty()) // 검색하는 문자열(=SearchText) 비워져있지 않다면
		{
			// 해당 DataAssetName에 SearchText 문자열이 포함되지 않는다면 보여주게 아니므로 continue.
			if (false == DataAssetName.Contains(SearchText.ToString())) continue;
		}

		RowDatas.Add(FWeaponRowData::Make(++Idx, DataAssetName, XZDA_Weapon)); // 데이터를 하나씩 넣어준다.
	}

	RowDatas.Sort([](const FWeaponRowDataPtr& A, const FWeaponRowDataPtr& B)
		{
			return A->Number < B->Number; // 오름차순 정렬
		});

	ListView->RequestListRefresh(); // 다른곳에서 사용하기 때문에 재갱신를 해준다.
}

void XZWeaponLeftArea::OnTextChanged(const FText& InText)
{
	// 예외처리. 기존 문자열과 현재 입력된 문자열이 같다면 리턴.
	if (SearchText.CompareToCaseIgnored(InText) == 0) return;

	SearchText = InText;
	ReadDataAssetList(); // 재검색
}

void XZWeaponLeftArea::OnTextCommitted(const FText& InText, ETextCommit::Type InType)
{
	OnTextChanged(InText);
}

void XZWeaponLeftArea::OnSelectedChanged(FWeaponRowDataPtr InDataPtr, ESelectInfo::Type InType)
{
	// 예외처리. 빈 구역 클릭 시 null로 값이 들어오므로 null일 시 리턴.
	if (false == InDataPtr.IsValid()) return;

	WeaponListViewSelectedItemDelegate.ExecuteIfBound(InDataPtr);
}

FText XZWeaponLeftArea::OnGetAssetCount() const
{
	FString str = FString::Printf(TEXT("%d Asset"), RowDatas.Num()); // 에셋

	return FText::FromString(str);
}
