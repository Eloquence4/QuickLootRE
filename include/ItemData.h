#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "ManagedEntryData.h"

#include "RE/Skyrim.h"

#undef GetForm


class ItemData;


namespace
{
	enum
	{
		kDebugType_Name,
		kDebugType_Count,
		kDebugType_Value,
		kDebugType_Weight,
		kDebugType_Type,
		kDebugType_Read,
		kDebugType_Enchanted,
		kDebugType_PickPocketChance,
		kDebugType_ValuePerWeight,
		kDebugType_Priority
	};


	using FnCompare = int(const ItemData& a_lhs, const ItemData& a_rhs);


	class CompareMap : public std::unordered_map<std::string, FnCompare*>
	{
	public:
		CompareMap();

		static int compareByName(const ItemData& a_lhs, const ItemData& a_rhs);
		static int r_compareByName(const ItemData& a_lhs, const ItemData& a_rhs);
		static int compareByCount(const ItemData& a_lhs, const ItemData& a_rhs);
		static int r_compareByCount(const ItemData& a_lhs, const ItemData& a_rhs);
		static int compareByValue(const ItemData& a_lhs, const ItemData& a_rhs);
		static int r_compareByValue(const ItemData& a_lhs, const ItemData& a_rhs);
		static int compareByWeight(const ItemData& a_lhs, const ItemData& a_rhs);
		static int r_compareByWeight(const ItemData& a_lhs, const ItemData& a_rhs);
		static int compareByType(const ItemData& a_lhs, const ItemData& a_rhs);
		static int r_compareByType(const ItemData& a_lhs, const ItemData& a_rhs);
		static int compareByRead(const ItemData& a_lhs, const ItemData& a_rhs);
		static int r_compareByRead(const ItemData& a_lhs, const ItemData& a_rhs);
		static int compareByEnchanted(const ItemData& a_lhs, const ItemData& a_rhs);
		static int r_compareByEnchanted(const ItemData& a_lhs, const ItemData& a_rhs);
		static int compareByPickPocketChance(const ItemData& a_lhs, const ItemData& a_rhs);
		static int r_compareByPickPocketChance(const ItemData& a_lhs, const ItemData& a_rhs);
		static int compareByPriority(const ItemData& a_lhs, const ItemData& a_rhs);
		static int r_compareByPriority(const ItemData& a_lhs, const ItemData& a_rhs);
		static int compareByValuePerWeight(const ItemData& a_lhs, const ItemData& a_rhs);
		static int r_compareByValuePerWeight(const ItemData& a_lhs, const ItemData& a_rhs);
	};
}


#define ITEM_DATA_DEBUG_ENABLED false
#if ITEM_DATA_DEBUG_ENABLED
#pragma message("ItemData debugging is enabled! Don't forget to disable it!")
#endif
#define ITEM_DATA_DEBUG_TYPE kDebugType_ValuePerWeight


class ItemData
{
public:
	ItemData();
	ItemData(const ItemData&) = default;
	ItemData(ItemData&&) = default;
	explicit ItemData(ManagedEntryDataPtr a_entryData);
	explicit ItemData(ManagedEntryDataPtr a_entryData, SInt32 a_count);
	~ItemData();

	static void SetCompareOrder();
	static void SetContainer(RE::TESObjectREFR* a_container);

	ItemData& operator=(const ItemData&) = default;
	ItemData& operator=(ItemData&&) = default;
	friend bool operator==(const ItemData& a_lhs, const ItemData& a_rhs);
	friend bool operator!=(const ItemData& a_lhs, const ItemData& a_rhs);
	friend bool operator< (const ItemData& a_lhs, const ItemData& a_rhs);
	friend bool operator> (const ItemData& a_lhs, const ItemData& a_rhs);
	friend bool operator<=(const ItemData& a_lhs, const ItemData& a_rhs);
	friend bool operator>=(const ItemData& a_lhs, const ItemData& a_rhs);

	RE::InventoryEntryData* GetEntryData() const;
	const char* GetName() const;
	SInt32 GetCount() const;
	SInt32 GetValue() const;
	float GetWeight() const;
	const char* GetIcon() const;
	bool GetIsStolen() const;
	bool GetIsRead() const;
	bool GetIsEnchanted() const;
	bool GetCanPickPocket() const;
	SInt32 GetPickPocketChance() const;
	RE::TESBoundObject* GetForm() const;
	template <class T, typename std::enable_if_t<std::is_convertible<T*, RE::TESBoundObject*>::value, int> = 0> T* GetForm() const;

	void ModCount(SInt32 a_mod);
	void DBGDumpType(std::size_t a_index);

private:
	friend class CompareMap;


	enum class Priority : UInt32
	{
		kKey,
		kGold,
		kLockPick,
		kAmmo,
		kSoulGem,
		kPotion,
		kPoison,
		kEnchantedWeapon,
		kEnchantedArmor,
		kGem,
		kAmulet,
		kRing,
		kWeapon,
		kArmor,
		kFood,
		kOther = kFood,
	};


	enum class Type : UInt32
	{
		kInvalid = static_cast<std::underlying_type_t<Type>>(-1),
		kNone = 0,

		kDefaultWeapon,
		kWeaponSword,
		kWeaponGreatSword,
		kWeaponDaedra,
		kWeaponDagger,
		kWeaponWarAxe,
		kWeaponBattleAxe,
		kWeaponMace,
		kWeaponHammer,
		kWeaponStaff,
		kWeaponBow,
		kWeaponArrow,
		kWeaponPickAxe,
		kWeaponWoodAxe,
		kWeaponCrossbow,
		kWeaponBolt,

		kDefaultArmor,

		kLightArmorBody,
		kLightArmorHead,
		kLightArmorHands,
		kLightArmorForearms,
		kLightArmorFeet,
		kLightArmorCalves,
		kLightArmorShield,
		kLightArmorMask,

		kArmorBody,
		kArmorHead,
		kArmorHands,
		kArmorForearms,
		kArmorFeet,
		kArmorCalves,
		kArmorShield,
		kArmorMask,
		kArmorBracer,
		kArmorDaedra,

		kClothingBody,
		kClothingRobe,
		kClothingHead,
		kClothingPants,
		kClothingHands,
		kClothingForearms,
		kClothingFeet,
		kClothingCalves,
		kClothingShoes,
		kClothingShield,
		kClothingMask,

		kArmorAmulet,
		kArmorRing,
		kCirclet,

		kDefaultScroll,
		kDefaultBook,
		kDefaultBookRead,
		kBookTome,
		kBookTomeRead,
		kBookJournal,
		kBookNote,
		kBookMap,

		kDefaultFood,
		kFoodWine,
		kFoodBeer,

		kDefaultIngredient,

		kDefaultKey,
		kKeyHouse,

		kDefaultPotion,
		kPotionHealth,
		kPotionStam,
		kPotionMagic,
		kPotionPoison,
		kPotionFrost,
		kPotionFire,
		kPotionShock,

		kDefaultMisc,
		kMiscArtifact,
		kMiscClutter,
		kMiscLockPick,
		kMiscSoulGem,

		kSoulGemEmpty,
		kSoulGemPartial,
		kSoulGemFull,
		kSoulGemGrandEmpty,
		kSoulGemGrandPartial,
		kSoulGemGrandFull,
		kSoulGemAzura,

		kMiscGem,
		kMiscOre,
		kMiscIngot,
		kMiscHide,
		kMiscStrips,
		kMiscLeather,
		kMiscWood,
		kMiscRemains,
		kMiscTrollSkull,
		kMiscTorch,
		kMiscGoldSack,	// coin purses are flora
		kMiscGold,
		kMiscDragonClaw
	};


	void ConstructCommon();

	float CalcWeight();
	Type CalcType();
	Type CalcTypeArmor(RE::TESObjectARMO* a_armor);
	Type CalcSpecialArmor(RE::FormID a_formID);
	Type CalcTypeBook(RE::TESObjectBOOK* a_book);
	Type CalcTypeMisc(RE::TESObjectMISC* a_misc);
	Type CalcTypeWeapon(RE::TESObjectWEAP* a_weap);
	Type CalcTypeKey(RE::TESKey* a_key);
	Type CalcTypePotion(RE::AlchemyItem* a_potion);
	Type CalcTypeSoulGem(RE::TESSoulGem* a_gem);
	bool CalcStolen();
	bool CalcRead();
	bool CalcEnchanted();
	bool CalcCanPickPocket();
	SInt32 CalcPickPocketChance();
	Priority CalcPriority();

	ManagedEntryDataPtr _entryData;
	const char* _name;
	SInt32 _count;
	SInt32 _value;
	float _weight;
	Type _type;
	bool _isStolen;
	bool _isRead;
	bool _isEnchanted;
	bool _canPickPocket;
	SInt32 _pickPocketChance;
	Priority _priority;

	static std::vector<FnCompare*> _compares;
	inline static RE::TESObjectREFR* _container = 0;

	static constexpr char* _strIcons[] = {
	"none",					// 00
	"default_weapon",
	"weapon_sword",
	"weapon_greatsword",
	"weapon_daedra",
	"weapon_dagger",
	"weapon_waraxe",
	"weapon_battleaxe",
	"weapon_mace",
	"weapon_hammer",
	"weapon_staff",			// 10
	"weapon_bow",
	"weapon_arrow",
	"weapon_pickaxe",
	"weapon_woodaxe",
	"weapon_crossbow",
	"weapon_bolt",
	"default_armor",
	"lightarmor_body",
	"lightarmor_head",
	"lightarmor_hands",		// 20
	"lightarmor_forearms",
	"lightarmor_feet",
	"lightarmor_calves",
	"lightarmor_shield",
	"lightarmor_mask",
	"armor_body",
	"armor_head",
	"armor_hands",
	"armor_forearms",
	"armor_feet",			// 30
	"armor_calves",
	"armor_shield",
	"armor_mask",
	"armor_bracer",
	"armor_daedra",
	"clothing_body",
	"clothing_robe",
	"clothing_head",
	"clothing_pants",
	"clothing_hands",		// 40
	"clothing_forearms",
	"clothing_feet",
	"clothing_calves",
	"clothing_shoes",
	"clothing_shield",
	"clothing_mask",
	"armor_amulet",
	"armor_ring",
	"armor_circlet",
	"default_scroll",		// 50
	"default_book",
	"default_book_read",
	"book_tome",
	"book_tome_read",
	"book_journal",
	"book_note",
	"book_map",
	"default_food",
	"food_wine",
	"food_beer",			// 60
	"default_ingredient",
	"default_key",
	"key_house",
	"default_potion",
	"potion_health",
	"potion_stam",
	"potion_magic",
	"potion_poison",
	"potion_frost",
	"potion_fire",			// 70
	"potion_shock",
	"default_misc",
	"misc_artifact",
	"misc_clutter",
	"misc_lockpick",
	"misc_soulgem",
	"soulgem_empty",
	"soulgem_partial",
	"soulgem_full",
	"soulgem_grandempty",	// 80
	"soulgem_grandpartial",
	"soulgem_grandfull",
	"soulgem_azura",
	"misc_gem",
	"misc_ore",
	"misc_ingot",
	"misc_hide",
	"misc_strips",
	"misc_leather",
	"misc_wood",			// 90
	"misc_remains",
	"misc_trollskull",
	"misc_torch",
	"misc_goldsack",
	"misc_gold",
	"misc_dragonclaw"
	};
};



template <class T, typename std::enable_if_t<std::is_convertible<T*, RE::TESBoundObject*>::value, int>>
T* ItemData::GetForm() const
{
	return static_cast<T*>(GetForm());
}
