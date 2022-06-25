void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 4, reset_day = 30;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, 8, 0);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, 8, 0);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, 8, 0);
			}
		}
	}
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.45, 0.65 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}
    
    EntityAI SpawnWithRandomHealth(PlayerBase player, string itemName)
    {
    	EntityAI itemEnt;
    
    	itemEnt = player.GetInventory().CreateInInventory(itemName);
        SetRandomHealth( itemEnt );
        
        return itemEnt;
    }

    void spawnItemNTimesOnPlayer(PlayerBase player, string item, int n) {
        for(int i = 0; i < n; i++) {
            player.GetInventory().CreateInInventory(item);
        }
    }

    void spawnItemsOnPlayer(PlayerBase player, TStringArray items) {
        for(int i = 0; i < items.Count(); i++) {
             player.GetInventory().CreateInInventory(items[i]);
        }
    }

    void spawnItemWithAttachments(PlayerBase player, string parentItem, TStringArray attachments) {
        EntityAI itemEnt;
        
        itemEnt = player.GetInventory().CreateInInventory(parentItem);

        for(int i = 0; i < attachments.Count(); i++) {
            itemEnt.GetInventory().CreateAttachment(attachments[i]);
        }   
    }

    // god dammit moitzbert
    string getItemNameForCamoType(string prefix, string camoType)
    {
        if (camoType == "green")
        {
            if(prefix == "MMG_Mag_Pouch_" || prefix == "MMG_JPC_Vest_" || prefix == "MMG_ammo_pouch_" || prefix == "MMG_Med_Pouch_" || prefix == "MMG_carrier_backpack_" || prefix == "MMG_assault_pack_" || prefix == "MMG_falcon_b1_belt_" || prefix == "MMG_sheath_" || prefix == "MMG_bottle_" || prefix == "MMG_combatpants_" || prefix == "MMG_balaclava_") {
                return prefix + "olive";
            }
        }

        return prefix + camoType;
    }

    void spawnRifle(PlayerBase player, string rifle) {
        autoptr TStringArray attachments;

        switch(rifle) {
            case "TTC_HK416Comp":
                attachments = {"TTC_Elcan","TTC_Universal_Suppressor_BLACK","TTC_DMR_VFG"};
                break;
            case "TTC_HK416Black":
                attachments = {"TTC_Elcan","TTC_Universal_Suppressor_BLACK","TTC_DMR_VFG","TTC_ButtstockHK_Black"};
                break;
            case "TTC_HK417":
                attachments = {"WE_AMSOptic","TTC_M14Suppressor","TTC_DMR_AFG","TTC_ButtstockHK_Black"};
                break;
            case "WE_SKS":
                player.GetInventory().CreateInInventory("WE_AMSOptic");
                attachments = {"WE_MosinSKSMount","TTC_Universal_Suppressor_BLACK"};
                break;
            case "TTC_MAS36":
            case "TTC_M1903":
            case "TTC_kar98k":
            case "TTC_R700":
                attachments = {"HuntingOptic", "TTC_M14Suppressor"};
                break;
        }

        spawnItemWithAttachments(player, rifle, attachments);
    }

    // spawn sidearm with full accessories and an extra mag.
    void spawnSidearm(PlayerBase player) {
        autoptr TStringArray pistols = {"TTC_P320", "TTC_Glock17", "TTC_Kimber"};
        autoptr TStringArray pistolMags = {"TTC_P320_17Rnd","TTC_Mag_Glock_17Rnd","Mag_Kimber1911_10Rnd"};
        autoptr TStringArray pistolAttachments = {"TTC_Pistol_Light","TTC_Pistol_Optic"};

        int rndIndex = Math.RandomInt(0, 3);

        spawnItemWithAttachments(player, pistols[rndIndex], pistolAttachments);

        player.GetInventory().CreateInInventory(pistolMags[rndIndex]);
        player.GetInventory().CreateInInventory(pistolMags[rndIndex]);

        if (rndIndex > 1) { // Kimber is .45
            spawnItemNTimesOnPlayer(player, "AmmoBox_45ACP_25rnd", 4);
        } else {
            spawnItemNTimesOnPlayer(player, "AmmoBox_9x19_25rnd", 4);
        }
    }

    void setInfantryStartingItems(PlayerBase player, string camoType)
    {
        string bag = getItemNameForCamoType("MMG_camelback_", camoType);
        string vest = getItemNameForCamoType("MMG_MK_III_Armor_", camoType);
        string belt = getItemNameForCamoType("MMG_falcon_b1_belt_", camoType);
        string helmet = getItemNameForCamoType("MMG_tactical_helmet_", camoType);

        autoptr TStringArray clothes = {getItemNameForCamoType("MMG_operatorshirt_", camoType), getItemNameForCamoType("MMG_combatpants_", camoType), getItemNameForCamoType("mmg_tactical_gloves_", camoType)};
        autoptr TStringArray bagAttachments = {getItemNameForCamoType("MMG_Med_Pouch_", camoType), getItemNameForCamoType("MMG_bottle_", camoType)};
        autoptr TStringArray vestAttachments = {getItemNameForCamoType("MMG_triple_magpouch_", camoType), getItemNameForCamoType("MMG_ammo_pouch_", camoType), getItemNameForCamoType("MMG_tactical_pouch_", camoType), getItemNameForCamoType("MMG_Med_Pouch_", camoType)};
        autoptr TStringArray beltAttachments = {getItemNameForCamoType("MMG_tactical_pouch_", camoType), getItemNameForCamoType("MMG_Med_Pouch_", camoType), getItemNameForCamoType("MMG_sheath_", camoType), getItemNameForCamoType("MMG_Holster_", camoType), getItemNameForCamoType("MMG_bottle_", camoType)};
        autoptr TStringArray helmetAttachments = {"UniversalLight"};   

        spawnItemWithAttachments(player, bag, bagAttachments);
        spawnItemsOnPlayer(player, clothes);
        spawnItemWithAttachments(player, vest, vestAttachments);
        spawnItemWithAttachments(player, belt, beltAttachments);
        spawnItemWithAttachments(player, helmet, helmetAttachments);
        spawnHeadphones(player, camoType);

        autoptr TStringArray rifles = {"TTC_SCARLBlack", "TTC_M16A4", "TTC_L85"};
        autoptr TStringArray rifleAttachments = {"TTC_Elcan", "UniversalLight", "Mag_STANAG_30Rnd"};

        int rndIndex = Math.RandomInt(0, 3);

        spawnItemWithAttachments(player, rifles[rndIndex], rifleAttachments);
        spawnSidearm(player);
        
        player.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
        player.GetInventory().CreateInInventory("ThickFramesGlasses");
        player.GetInventory().CreateInInventory("NioshFaceMask");
    }

    void setSniperStartingItems(PlayerBase player, string camoType)
    {
        Debug.LogInfo("generating sniper for camo type: " + camoType);

        string vest = getItemNameForCamoType("MMG_chestrig_", camoType);
        
        if (camoType == "sweden"){
            // current version of MMG Country Camo is missing sweden camo chestrig
            vest = getItemNameForCamoType("MMG_chestrig_", "green");
        } 

        string belt = getItemNameForCamoType("MMG_falcon_b1_belt_", camoType);

        autoptr TStringArray clothes = {getItemNameForCamoType("MMG_carrier_backpack_", camoType), getItemNameForCamoType("MMG_combatshirt_", camoType), getItemNameForCamoType("MMG_combatpants_", camoType), getItemNameForCamoType("mmg_tactical_gloves_", camoType), getItemNameForCamoType("MMG_balaclava_", camoType), "NVGHeadstrap", "NVGoggles"};
        autoptr TStringArray vestAttachments = {getItemNameForCamoType("MMG_tactical_pouch_", camoType), getItemNameForCamoType("MMG_Med_Pouch_", camoType), getItemNameForCamoType("MMG_bottle_", camoType), getItemNameForCamoType("MMG_sheath_", camoType)};
        autoptr TStringArray beltAttachments = {getItemNameForCamoType("MMG_tactical_pouch_", camoType), getItemNameForCamoType("MMG_Med_Pouch_", camoType), getItemNameForCamoType("MMG_sheath_", camoType), getItemNameForCamoType("MMG_Holster_", camoType), getItemNameForCamoType("MMG_bottle_", camoType)};   

        spawnItemsOnPlayer(player, clothes);
        spawnItemWithAttachments(player, vest, vestAttachments);
        spawnItemWithAttachments(player, belt, beltAttachments);

        switch(camoType){
            case "black":
                // black is the only camo scheme without its own sniper boonie
                player.GetInventory().CreateInInventory("mmg_boonie_dark_woodland");
                break;
            default:
                player.GetInventory().CreateInInventory("mmg_boonie_" + camoType);
                break;
        }

        autoptr TStringArray rifles = {"TTC_XM2010", "WE_M14", "WE_R700", "TTC_MAS36"};
        autoptr TStringArray rifleMagazines = {"TTC_XM2010_10rnd", "WE_Mag_M14_10Rnd", "WE_Mag_R700_10Rnd"};
        autoptr TStringArray rifleScopes = {"TTC_VortexRHDAMG_Optic", "WE_AMSOptic", "HuntingOptic", "HuntingOptic"};
        autoptr TStringArray rifleSuppressors = {"TTC_M14Suppressor", "WE_308Suppressor", "WE_308Suppressor", "TTC_M14Suppressor"};

        int rndIndex = Math.RandomInt(0, 4);

        autoptr TStringArray rifleAttachments = new TStringArray;
        rifleAttachments.Insert(rifleScopes[rndIndex]);
        rifleAttachments.Insert(rifleSuppressors[rndIndex]);

        // spawn ammo box or extra mag
        if (rndIndex < 3) {
            rifleAttachments.Insert(rifleMagazines[rndIndex]);
            player.GetInventory().CreateInInventory(rifleMagazines[rndIndex]);
        } else {
            // MAS 36 has internal mag
            player.GetInventory().CreateInInventory("AmmoBox_762x54_20Rnd");
        }

        // spawn rifle itself with expected accessories
        spawnItemWithAttachments(player, rifles[rndIndex], rifleAttachments);
        spawnSidearm(player);
        player.GetInventory().CreateInInventory("TTC_PistolSuppressor");
        player.GetInventory().CreateInInventory("Rangefinder");
    }

    void setDesignatedMarksmanStartingItems(PlayerBase player, string camoType)
    {
        string bag = getItemNameForCamoType("MMG_camelback_", camoType);
        string vest = getItemNameForCamoType("MMG_tt_Vest_", camoType);
        string belt = getItemNameForCamoType("MMG_falcon_b1_belt_", camoType);
        string helmet = getItemNameForCamoType("MMG_tactical_helmet_", camoType);

        autoptr TStringArray clothes = {getItemNameForCamoType("MMG_tactical_shirt_", camoType), getItemNameForCamoType("MMG_combatpants_", camoType), getItemNameForCamoType("mmg_tactical_gloves_", camoType),  getItemNameForCamoType("MMG_balaclava_", camoType)};
        autoptr TStringArray bagAttachments = {getItemNameForCamoType("MMG_Med_Pouch_", camoType), getItemNameForCamoType("MMG_bottle_", camoType)};
        autoptr TStringArray vestAttachments = {getItemNameForCamoType("MMG_ammo_pouch_", camoType), getItemNameForCamoType("MMG_ammo_pouch_", camoType), getItemNameForCamoType("MMG_tactical_pouch_", camoType), getItemNameForCamoType("MMG_Med_Pouch_", camoType), getItemNameForCamoType("MMG_bottle_", camoType)};
        autoptr TStringArray beltAttachments = {getItemNameForCamoType("MMG_tactical_pouch_", camoType), getItemNameForCamoType("MMG_Med_Pouch_", camoType), getItemNameForCamoType("MMG_sheath_", camoType), getItemNameForCamoType("MMG_Holster_", camoType), getItemNameForCamoType("MMG_bottle_", camoType)};
        autoptr TStringArray helmetAttachments = {"UniversalLight"};   

        spawnItemWithAttachments(player, bag, bagAttachments);
        spawnItemsOnPlayer(player, clothes);
        spawnItemWithAttachments(player, vest, vestAttachments);
        spawnItemWithAttachments(player, belt, beltAttachments);
        spawnItemWithAttachments(player, helmet, helmetAttachments);
        spawnHeadphones(player, camoType);

        autoptr TStringArray rifles = {"TTC_HK417", "TTC_HKG28_Black", "TTC_SCARHBlack", "TTC_M110_Black", "TTCSR25", "TTC_M4DMR"};
        autoptr TStringArray rifleMagazines = {"TTC_HK417_Magazine_20rnd", "TTC_HK417_Magazine_20rnd", "TTC_SCARHMag", "TTC_308Stanag", "TTC_308Stanag", "TTC_308Stanag"};
        autoptr TStringArray rifleAttachments = {"TTC_VortexSE_Optic"};

        int rndIndex = Math.RandomInt(0, 6);

        rifleAttachments.Insert(rifleMagazines[rndIndex]);
        player.GetInventory().CreateInInventory(rifleMagazines[rndIndex]);

        if (rndIndex < 2) {
            // HK DMRs have their own buttstock
            rifleAttachments.Insert("TTC_ButtstockHK_Black");
            rifleAttachments.Insert("TTC_DMR_VFG");
        } else if (rndIndex > 2 && rndIndex < 5) {
            // ignore the SCAR-H, it doesn't have this slot, and the M4DMR does its own thing
            rifleAttachments.Insert("TTC_DMR_VFG");
        } else if (rndIndex == 5) {
            // M4DMR has this weird handguard thing that only it uses
            rifleAttachments.Insert("TTC_DMR_Hndguard");
        }

        spawnItemWithAttachments(player, rifles[rndIndex], rifleAttachments);
        spawnSidearm(player);
        // probably doesn't make sense for a DM to need glasses but i just like them okay
        player.GetInventory().CreateInInventory("ThickFramesGlasses");
        player.GetInventory().CreateInInventory("Rangefinder");
    }

    void setHeavyGunnerStartingItems(PlayerBase player, string camoType)
    {
        string vest = getItemNameForCamoType("MMG_MK_V_Armor_", camoType);
        string belt = getItemNameForCamoType("MMG_falcon_b1_belt_", camoType);
        string helmet = getItemNameForCamoType("MMG_striker_helmet_", camoType);

        autoptr TStringArray clothes = {getItemNameForCamoType("MMG_supplybag_", camoType), getItemNameForCamoType("MMG_operatorshirt_", camoType), getItemNameForCamoType("MMG_combatpants_", camoType), getItemNameForCamoType("mmg_tactical_gloves_", camoType), getItemNameForCamoType("MMG_balaclava_", camoType)};
        autoptr TStringArray vestAttachments = {getItemNameForCamoType("MMG_Holster_", camoType), getItemNameForCamoType("MMG_ammo_pouch_", camoType), getItemNameForCamoType("MMG_ammo_pouch_", camoType), getItemNameForCamoType("MMG_mk5_utility_pouch_", camoType), getItemNameForCamoType("MMG_mk5_grenade_pouch_", camoType), getItemNameForCamoType("MMG_sheath_", camoType)};
        autoptr TStringArray beltAttachments = {getItemNameForCamoType("MMG_tactical_pouch_", camoType), getItemNameForCamoType("MMG_Med_Pouch_", camoType), getItemNameForCamoType("MMG_sheath_", camoType), getItemNameForCamoType("MMG_Holster_", camoType), getItemNameForCamoType("MMG_bottle_", camoType)};
        autoptr TStringArray helmetAttachments = {"UniversalLight"};   

        spawnItemsOnPlayer(player, clothes);
        spawnItemWithAttachments(player, vest, vestAttachments);
        spawnItemWithAttachments(player, belt, beltAttachments);
        spawnItemWithAttachments(player, helmet, helmetAttachments);

        // we don't have LMGs in dayz, or, at least not in the mods i use, so i guess give him a battle rifle
        autoptr TStringArray rifles = {"TTC_AG3", "TTC_FAL", "TTC_G3"};
        autoptr TStringArray rifleMagazines = {"TTC_AG3_Coupled_Magazine_40rnd", "TTC_Coupled_FAL_Magazine", "TTC_AG3_Coupled_Magazine_40rnd"};
        autoptr TStringArray rifleScopes = {"TTC_VortexSE_Optic", "TTC_VortexSE_Optic", "TTC_G3_Optic"};

        int rndIndex = Math.RandomInt(0, 3);

        autoptr TStringArray rifleAttachments = new TStringArray;
        rifleAttachments.Insert(rifleScopes[rndIndex]);
        rifleAttachments.Insert(rifleMagazines[rndIndex]);
        player.GetInventory().CreateInInventory(rifleMagazines[rndIndex]);

        spawnItemWithAttachments(player, rifles[rndIndex], rifleAttachments);
        spawnSidearm(player);
    }

    // yet another special case
    void spawnHeadphones(PlayerBase player, string camoType)
    {
        switch(camoType) { 
            case "multicam":
            case "ucp":
            case "green":
            case "erdl":
            case "multicam_tropic":
            case "ukraine":
            case "germany":
            case "sweden":
            case "norway":
                player.GetInventory().CreateInInventory("MMG_headphones_green");
                break;
            case "black":
            case "dark_woodland":
            case "multicamblack":
                player.GetInventory().CreateInInventory("MMG_headphones_black");
                break;
        }
    }

    void setSoldierStartingItems(PlayerBase player)
    {
        string soldierTypes[] = {"sniper","designated marksman","infantry","heavy gunner"};
        string camoSchemes[] = {"multicam","erdl","ucp","black","tan","green","multicam_tropic","multicamblack","germany","norway","sweden","ukraine"};

        int rndIndex = Math.RandomInt(0, 12);
        string camoType = camoSchemes[rndIndex];

        rndIndex = Math.RandomInt(0,4);
        string soldierType = soldierTypes[rndIndex];

        switch(soldierType)
        {
            case "sniper":
                setSniperStartingItems(player, camoType);
                break;
            case "designated marksman":
                setDesignatedMarksmanStartingItems(player, camoType);
                break;
            case "infantry":
                setInfantryStartingItems(player, camoType);
                break;
            case "heavy gunner":
                setHeavyGunnerStartingItems(player, camoType);
                break;
        }

        autoptr TStringArray specialCaseItems;

        switch(camoType) { 
            case "tan":
            case "multicam":
                specialCaseItems = {"High_Knee_Sneakers", "MMG_carbine_grey"};
                break;
            case "erdl":
                specialCaseItems = {"SK8_Sneakers_FullBlack", "MMG_carbine_black"};
                break;
            case "ucp":
                specialCaseItems = {"SK8_Sneakers_Black", "MMG_carbine_grey"};
                break;
            case "black":
                specialCaseItems = {"SK8_Sneakers_FullBlack", "MMG_carbine_black"};
                break;
            case "dark_woodland":
                specialCaseItems = {"SK8_Sneakers_FullBlack", "MMG_carbine_black"};
                break;
            case "green":
                specialCaseItems = {"SK8_Sneakers_Black", "MMG_carbine_green"};
                break;
            case "multicam_tropic":
                specialCaseItems = {"SK8_Sneakers_Black", "MMG_carbine_green"};
                break;
            case "multicamblack":
                specialCaseItems = {"SK8_Sneakers_FullBlack", "MMG_carbine_black"};
                break;
            default:
                specialCaseItems = {"SK8_Sneakers_FullBlack", "MMG_carbine_black"};
                break;
        }

        spawnItemsOnPlayer(player, specialCaseItems);

        player.GetInventory().CreateInInventory("Battery9V");
        player.GetInventory().CreateInInventory("Battery9V");
        player.GetInventory().CreateInInventory("CombatKnife");
    }

    void setFirefighterStartingItems(PlayerBase player)
    {
        EntityAI itemEnt;
        float rand;

        string head[] = {"FirefightersHelmet_Red","FirefightersHelmet_White","FirefightersHelmet_Yellow"};

        int rndIndex = Math.RandomInt(0, 3);

        itemEnt = SpawnWithRandomHealth(player, head[rndIndex]);

        string torso[] = {"FirefighterJacket_Beige", "FirefighterJacket_Black"};
        string legs[] = {"FirefightersPants_Beige", "FirefightersPants_Black"};
        string feet[] = {"Wellies_Brown", "Wellies_Black"};

        rndIndex = Math.RandomInt(0, 2);
        
        itemEnt = SpawnWithRandomHealth(player, torso[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, legs[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, feet[rndIndex]);

        rand = Math.RandomFloatInclusive( 0.0, 1.0 );
        if ( rand < 0.25 )
        {
            itemEnt = SpawnWithRandomHealth(player, "AirborneMask");
        }

        rand = Math.RandomFloatInclusive( 0.0, 1.0 );
        if ( rand < 0.5 )
        {
            itemEnt = SpawnWithRandomHealth(player, "FirefighterAxe");
        }
    }

    void setDirtBikerStartingItems(PlayerBase player)
    {
        EntityAI itemEnt; 

        string head[] = {"DirtBikeHelmet_Black","DirtBikeHelmet_Blue","DirtBikeHelmet_Chernarus", "DirtBikeHelmet_Green", "DirtBikeHelmet_Khaki", "DirtBikeHelmet_Police", "DirtBikeHelmet_Red"};
        string legs[] = {"CargoPants_Black", "CargoPants_Blue", "CargoPants_Green", "CargoPants_Green", "BDUPants", "CargoPants_Grey", "CargoPants_Grey"};

        int rndIndex = Math.RandomInt(0, 7);

        itemEnt = SpawnWithRandomHealth(player, head[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, "DirtBikeHelmet_Mouthguard");
        itemEnt = SpawnWithRandomHealth(player, "DirtBikeHelmet_Visor");
        itemEnt = SpawnWithRandomHealth(player, "RidersJacket_Black");
        itemEnt = SpawnWithRandomHealth(player, legs[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, "TTSKOBoots");

        itemEnt = SpawnWithRandomHealth(player, "Wrench");
        itemEnt = SpawnWithRandomHealth(player, "TireRepairKit");
    }

    void setSkateboarderStartingItems(PlayerBase player)
    {
        EntityAI itemEnt;

        string head[] = {"SkateHelmet_Black","SkateHelmet_Blue","SkateHelmet_Gray", "SkateHelmet_Green", "SkateHelmet_Red"};
        string torso[] = {"Hoodie_Black","Hoodie_Blue","Hoodie_Grey","Hoodie_Green", "Hoodie_Red"};
        string legs[] = {"Jeans_Black", "Jeans_BlueDark", "Jeans_Grey", "Jeans_Green", "Jeans_Black"};
        string feet[] = {"SK8_Sneakers_FullBlack", "SK8_Sneakers_Blue","High_Knee_Sneakers_Black", "High_Knee_Sneakers", "SK8_Sneakers_Black"};
        string bag[] = { "Canvas_Backpack_Black", "Canvas_Backpack_Blue", "Canvas_Backpack_Base", "Canvas_Backpack_Base", "Canvas_Backpack_Red"};

        int rndIndex = Math.RandomInt(0, 5);

        itemEnt = SpawnWithRandomHealth(player, head[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, torso[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, legs[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, feet[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, bag[rndIndex]);
    }

    void setEscapedPrisonerStartingItems(PlayerBase player)
    {
        EntityAI itemEnt;

        itemEnt = SpawnWithRandomHealth(player, "HockeyMask");
        itemEnt = SpawnWithRandomHealth(player, "PrisonUniformJacket");
        itemEnt = SpawnWithRandomHealth(player, "PrisonUniformPants");
        itemEnt = SpawnWithRandomHealth(player, "JoggingShoes_White");
        itemEnt = SpawnWithRandomHealth(player, "LeatherSack_Beige");
        itemEnt = SpawnWithRandomHealth(player, "Rope");
        itemEnt = SpawnWithRandomHealth(player, "DuctTape");
        itemEnt = SpawnWithRandomHealth(player, "KitchenKnife");
    }
    
    void setBikerStartingItems(PlayerBase player)
    {
    	EntityAI itemEnt;
        float rand;
        
    	string head[] = {"DarkMotoHelmet_Black","DarkMotoHelmet_Blue","DarkMotoHelmet_Red"};
        string legs[] = {"Jeans_Black", "Jeans_Grey", "Jeans_BlueDark"};
        string feet[] = {"MilitaryBoots_Redpunk", "MilitaryBoots_Bluerock","MilitaryBoots_Redpunk"};
        string neck[] = {"Bandana_Blackpattern","Bandana_Blackpattern","Bandana_Redpattern"};
        
        int rndIndex = Math.RandomInt( 0, 3 );
        
        itemEnt = SpawnWithRandomHealth(player, head[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, legs[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, feet[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, neck[rndIndex]);
        
        itemEnt = SpawnWithRandomHealth(player, "RidersJacket_Black");
        itemEnt = SpawnWithRandomHealth(player, "AviatorGlasses");
        itemEnt = SpawnWithRandomHealth(player, "PetrolLighter");
        
        rand = Math.RandomFloatInclusive( 0.0, 1.0 );
			
        if ( rand < 0.25 )
        {
	    itemEnt = SpawnWithRandomHealth(player, "TTC_44Magnum_Black");
            itemEnt = player.GetInventory().CreateInInventory("TTC_Ammo_44Mag");
        } else {
	    itemEnt = SpawnWithRandomHealth(player, "Magnum");
            itemEnt = player.GetInventory().CreateInInventory("Ammo_357");
        }
    }
    
    void setBackpackerStartingItems(PlayerBase player)
    {
        EntityAI itemEnt;
        ItemBase itemBs;
    
    	string head[] = {"BeanieHat_Black","BeanieHat_Blue","BeanieHat_Green","BeanieHat_Red","BeanieHat_Grey","BeanieHat_Beige","BeanieHat_Pink","BeanieHat_Beige"};
        string torso[] = {"QuiltedJacket_Black","QuiltedJacket_Blue","QuiltedJacket_Green","QuiltedJacket_Red", "QuiltedJacket_Grey", "QuiltedJacket_Orange", "QuiltedJacket_Violet", "QuiltedJacket_Yellow"};
        string legs[] = {"HunterPants_Spring", "HunterPants_Brown", "HunterPants_Spring", "HunterPants_Brown", "HunterPants_Spring", "HunterPants_Brown", "HunterPants_Brown", "HunterPants_Spring"};
        string feet[] = {"HikingBoots_Black", "HikingBoots_Brown", "HikingBoots_Brown","HikingBoots_Brown", "HikingBoots_Black", "HikingBoots_Brown", "HikingBoots_Black", "HikingBoots_Black"};
        string bag[] = {"MountainBag_Green", "MountainBag_Blue", "MountainBag_Green", "MountainBag_Orange", "MountainBag_Green", "MountainBag_Orange",  "MountainBag_Blue", "MountainBag_Orange" };
        
        int rndIndex = Math.RandomInt( 0, 8 );
        
        itemEnt = SpawnWithRandomHealth(player, head[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, torso[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, legs[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, feet[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, bag[rndIndex]);
        
        itemEnt = player.GetInventory().CreateInInventory("Battery9V");
        itemEnt = player.GetInventory().CreateInInventory("Flashlight");
        itemEnt = player.GetInventory().CreateInInventory("HuntingKnife");
        itemEnt = player.GetInventory().CreateInInventory("Canteen");
        itemEnt = player.GetInventory().CreateInInventory("Hatchet");
        itemEnt = player.GetInventory().CreateInInventory("PurificationTablets");
        
        if (Class.CastTo(itemBs, itemEnt)) {
			itemBs.SetQuantity(Math.RandomInt(1, 10));
        }
    }
    
    void setHikerStartingItems(PlayerBase player)
    {
        EntityAI itemEnt;
    
    	string head[] = {"BoonieHat_Black","BoonieHat_NavyBlue","BoonieHat_Olive","BoonieHat_Red"};
        string torso[] = {"HikingJacket_Black","HikingJacket_Blue","HikingJacket_Green","HikingJacket_Red"};
        string legs[] = {"HunterPants_Spring", "HunterPants_Brown", "HunterPants_Spring", "HunterPants_Brown"};
        string feet[] = {"HikingBootsLow_Black", "HikingBootsLow_Blue", "HikingBootsLow_Grey","HikingBootsLow_Beige"};
        string bag[] = {"Spur_Treker_Black", "Spur_Treker_Blue", "Spur_Treker_Green", "Spur_Treker_Red"};
        
        int rndIndex = Math.RandomInt( 0, 4 );
        
        itemEnt = SpawnWithRandomHealth(player, head[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, torso[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, legs[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, feet[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, bag[rndIndex]);
        
        itemEnt = player.GetInventory().CreateInInventory("Battery9V");
        itemEnt = player.GetInventory().CreateInInventory("Flashlight");
        itemEnt = player.GetInventory().CreateInInventory("HuntingKnife");
        itemEnt = player.GetInventory().CreateInInventory("WaterBottle");
    }
    
    void setHunterStartingItems(PlayerBase player)
    {
    	string head[] = {"Ushanka_Green", "Ushanka_Green", "Ushanka_Black", "Ushanka_Black"};
        string jackets[] = {"HuntingJacket_Spring", "HuntingJacket_Summer", "HuntingJacket_Autumn", "HuntingJacket_Brown"};
        string pants[] = {"HunterPants_Spring", "HunterPants_Summer", "HunterPants_Autumn", "HunterPants_Brown"};
        string feet[] = {"CombatBoots_Green", "CombatBoots_Green", "CombatBoots_Brown", "CombatBoots_Brown"};
        
        EntityAI itemEnt;
        ItemBase itemBs;
        
        int rndIndex = Math.RandomInt( 0, 4 );
        
	    itemEnt = SpawnWithRandomHealth(player, "HuntingBag");
	    itemEnt = SpawnWithRandomHealth(player, head[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, jackets[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, pants[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, feet[rndIndex]);
        
        itemEnt = player.GetInventory().CreateInInventory("Battery9V");
        itemEnt = player.GetInventory().CreateInInventory("Flashlight");
        itemEnt = player.GetInventory().CreateInInventory("NylonKnifeSheath");
        itemEnt.GetInventory().CreateAttachment("HuntingKnife");
        itemEnt = player.GetInventory().CreateInInventory("Machete");
        itemEnt = player.GetInventory().CreateInInventory("Canteen");
        
        string rifles[] = {"CZ527","WE_Mosin9130","WE_SKS","Winchester70","TTC_R700","TTC_kar98k","TTC_LeeEnfield", "TTC_M1903", "TTC_MAS36", "TTC_Winchester1873", "B95"};
        string ammoTypes[] = {"Mag_CZ527_5rnd", "Ammo_762x54", "Ammo_762x54", "Ammo_308Win", "Ammo_308Win", "TTC_Ammo_8mm", "TTC_Ammo_303", "TTC_Ammo_3006", "Ammo_762x54", "TTC_Ammo_4570", "Ammo_308Win"};
        string scopes[] = {"HuntingOptic", "PUScopeOptic", "PUScopeOptic", "HuntingOptic", "HuntingOptic", "HuntingOptic", "PUScopeOptic", "PUScopeOptic", "HuntingOptic", "HuntingOptic", "HuntingOptic"};

        rndIndex = Math.RandomInt(0, 11);
        
        itemEnt = SpawnWithRandomHealth(player, rifles[rndIndex]);
        itemEnt.GetInventory().CreateAttachment(scopes[rndIndex]);
        itemEnt = player.GetInventory().CreateInInventory(ammoTypes[rndIndex]);
    }
    
    void setIndustrialStartingItems(PlayerBase player)
    {
    	EntityAI itemEnt;
    
    	string head[] = {"ConstructionHelmet_White","ConstructionHelmet_Lime","ConstructionHelmet_Yellow","ConstructionHelmet_Orange","ConstructionHelmet_Red","ConstructionHelmet_Blue"};
        string torso[] = {"JumpsuitJacket_Gray","JumpsuitJacket_Green","JumpsuitJacket_Gray","JumpsuitJacket_Gray","JumpsuitJacket_Red","JumpsuitJacket_Blue"};
        string legs[] = {"JumpsuitPants_Grey","JumpsuitPants_Green","JumpsuitPants_Grey","JumpsuitPants_Grey","JumpsuitPants_Red","JumpsuitPants_Blue"};
        string bag[] = {"DryBag_Black","DryBag_Green","DryBag_Yellow","DryBag_Orange","DryBag_Red","DryBag_Blue"};
        
        int rndIndex = Math.RandomInt( 0, 6 );
        
        itemEnt = SpawnWithRandomHealth(player, head[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, torso[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, legs[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, bag[rndIndex]);
        
        itemEnt = SpawnWithRandomHealth(player, "ReflexVest");
        itemEnt = SpawnWithRandomHealth(player, "NioshFaceMask");
        itemEnt = SpawnWithRandomHealth(player, "WorkingBoots_Yellow");
        itemEnt = SpawnWithRandomHealth(player, "WorkingGloves_Beige");
        
        string tools[] = {"Pipe","PipeWrench","Crowbar","Pickaxe","Shovel"};
        
        rndIndex = Math.RandomInt( 0, 6 );

        itemEnt = SpawnWithRandomHealth(player, tools[rndIndex]);
    }
    
    void setPoliceStartingItems(PlayerBase player) 
    {
        string head[] = {"PoliceCap", "PoliceCap", "MMG_tactical_helmet_police"};
        string torso[] = {"PoliceJacket", "PoliceJacketOrel", "MMG_combatshirt_police"};
        string vest[] = {"ChestHolster", "PoliceVest", "MMG_tt_Vest_police"};
        string legs[] = {"PolicePants", "PolicePantsOrel", "MMG_combatpants_police"};
        
        EntityAI itemEnt;
        ItemBase itemBs;
        float rand;
     
        int rndIndex = Math.RandomInt( 0, 3 );
        
        itemEnt = SpawnWithRandomHealth(player, head[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, torso[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, vest[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, legs[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, "CombatBoots_Black");
        
        if (rndIndex < 2) {            
            itemEnt = player.GetInventory().CreateInInventory("Battery9V");
        	itemEnt = player.GetInventory().CreateInInventory("Flashlight");
        } else {
            itemEnt = SpawnWithRandomHealth(player, "MMG_assault_pack_black");
			
            itemEnt = player.GetInventory().CreateInInventory("Battery9V");
            itemEnt = player.GetInventory().CreateInInventory("Battery9V");
       		itemEnt = player.GetInventory().CreateInInventory("UniversalLight");
        	itemEnt = player.GetInventory().CreateInInventory("MMG_headphones_black");
            
           	rand = Math.RandomFloatInclusive( 0.0, 1.0 );
			if ( rand < 0.25 )
            {
				itemEnt = SpawnWithRandomHealth(player, "TTC_Mossberg");
                itemEnt = player.GetInventory().CreateInInventory("Ammo_12gaPellets");
            }
        }
        
        string sideArm = "TTC_Glock17";
        autoptr TStringArray sideArmAttachments = {"TTC_Mag_Glock_17Rnd", "TTC_Pistol_Light"};

        spawnItemWithAttachments(player, sideArm, sideArmAttachments);
    }
    
    void setMedicStartingItems(PlayerBase player)
    {
    	string head[] = {"BeanieHat_Red", "BeanieHat_Green", "BeanieHat_Blue"};
        string jackets[] = {"ParamedicJacket_Crimson", "ParamedicJacket_Green", "ParamedicJacket_Blue"};
        string pants[] = {"ParamedicPants_Crimson", "ParamedicPants_Green", "ParamedicPants_Blue"};
        string gloves[] = {"SurgicalGloves_LightBlue", "SurgicalGloves_Green", "SurgicalGloves_Blue"};
     
     	EntityAI itemEnt;
     
        int rndIndex = Math.RandomInt( 0, 3 );
        
        SpawnWithRandomHealth(player, head[rndIndex]);
        SpawnWithRandomHealth(player, jackets[rndIndex]);
        SpawnWithRandomHealth(player, pants[rndIndex]);
        SpawnWithRandomHealth(player, gloves[rndIndex]);
        
        SpawnWithRandomHealth(player, "WorkingBoots_Brown");
        
        SpawnWithRandomHealth(player, "Flaregun");
        
        string flareColors[] = {"Ammo_Flare","Ammo_FlareBlue","Ammo_FlareGreen","Ammo_FlareRed"};
        rndIndex = Math.RandomInt( 0, 4 );
        
        player.GetInventory().CreateInInventory(flareColors[rndIndex]);
        
        SpawnWithRandomHealth(player, "SurgicalMask");
        itemEnt = SpawnWithRandomHealth(player, "FirstAidKit");
        
        itemEnt = player.GetInventory().CreateInInventory("BandageDressing");
		itemEnt = player.GetInventory().CreateInInventory("BandageDressing");
        itemEnt = player.GetInventory().CreateInInventory("Epinephrine");
        itemEnt = player.GetInventory().CreateInInventory("Morphine");
        itemEnt = player.GetInventory().CreateInInventory("StartKitIV");
        itemEnt = player.GetInventory().CreateInInventory("SalineBag");
        itemEnt = player.GetInventory().CreateInInventory("BloodBagEmpty");
        itemEnt = player.GetInventory().CreateInInventory("BloodTestKit");
    }
    
    void setTownspersonStartingItems(PlayerBase player)
    {
    	EntityAI itemEnt;
    
    	string pantsArray[] = { "Jeans_Black", "Jeans_Blue", "Jeans_BlueDark", "Jeans_Brown", "Jeans_Green", "Jeans_Grey"};
        string topArray[] = { "Layered_Shirt_Cheburashka", "Layered_Shirt_Courage", "Layered_Shirt_Lily", "Layered_Shirt_White", "Layered_Shirt_Base", "Medium_Sleeves_Shirt", "Medium_Sleeves_Shirt_Red", "Medium_Sleeves_Shirt_Blue"};
        string bagArray[] = { "Canvas_Backpack_Base", "Canvas_Backpack_Black", "Canvas_Backpack_White", "Canvas_Backpack_Red", "Canvas_Backpack_Blue", "Canvas_Backpack_Purple"};
        string shoesArray[] = { "SK8_Sneakers_Black", "SK8_Sneakers_FullBlack", "SK8_Sneakers_Blue", "Sneakers_Black", "Sneakers_Gray", "Sneakers_Green", "Sneakers_Red", "Sneakers_White"};
        
		int rndIndex = Math.RandomInt( 0, 6 );
		itemEnt = SpawnWithRandomHealth(player, pantsArray[rndIndex]);
            
		rndIndex = Math.RandomInt( 0, 8 );
		itemEnt = SpawnWithRandomHealth(player, topArray[rndIndex]);
        
		rndIndex = Math.RandomInt( 0, 6 );
		itemEnt = SpawnWithRandomHealth(player, bagArray[rndIndex]);
            
		rndIndex = Math.RandomInt( 0, 7 );
		itemEnt = SpawnWithRandomHealth(player, shoesArray[rndIndex]);

        itemEnt = player.GetInventory().CreateInInventory("Battery9V");
        itemEnt = player.GetInventory().CreateInInventory("Flashlight");
        itemEnt = player.GetInventory().CreateInInventory("HuntingKnife");
    }

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}

    void SpawnJeffSetup(PlayerBase player) {
        string camoType = "alpine";
        string spurgleCamo = "WinterCamo";

        autoptr TStringArray clothes = {"BeanieHat_Black","ThickFramesGlasses","NioshFaceMask","QuiltedJacket_Black",getItemNameForCamoType("mmg_tactical_gloves_", camoType),"Jeans_Black","SK8_Sneakers_Black"};

        spawnItemsOnPlayer(player, clothes);

        string bag = "Spur_CamelBag_" + spurgleCamo;
        autoptr TStringArray bagAttachments = {"SmershBag_Spur_" + spurgleCamo,"PlateCarrierHolster_Spur_" + spurgleCamo,"Spur_KnifeSheath_Black","PersonalRadio"};

        spawnItemWithAttachments(player, bag, bagAttachments);

        string belt = getItemNameForCamoType("MMG_falcon_b1_belt_", camoType);
        autoptr TStringArray beltAttachments = {getItemNameForCamoType("MMG_tactical_pouch_", camoType), getItemNameForCamoType("MMG_Med_Pouch_", camoType), getItemNameForCamoType("MMG_sheath_", camoType), getItemNameForCamoType("MMG_Holster_", camoType), getItemNameForCamoType("MMG_bottle_", camoType)};

        spawnItemWithAttachments(player, belt, beltAttachments);

        string vest = getItemNameForCamoType("MMG_tt_Vest_", camoType);
        autoptr TStringArray vestAttachments = {getItemNameForCamoType("MMG_ammo_pouch_", camoType), getItemNameForCamoType("MMG_ammo_pouch_", camoType), getItemNameForCamoType("MMG_tactical_pouch_", camoType), getItemNameForCamoType("MMG_Med_Pouch_", camoType), getItemNameForCamoType("MMG_bottle_", camoType)};

        spawnItemWithAttachments(player, vest, vestAttachments);

        spawnRifle(player, "TTC_SCARLSnow");
        spawnItemNTimesOnPlayer(player, "TTC_DMR_556Pmag_40rnd", 3);
        spawnItemNTimesOnPlayer(player, "AmmoBox_556x45_20Rnd", 12);

        spawnRifle(player, "TTC_MAS36");
        spawnItemNTimesOnPlayer(player, "AmmoBox_762x54_20Rnd", 12);

        spawnSidearm(player);
        player.GetInventory().CreateInInventory("TTC_PistolSuppressor");

        player.GetInventory().CreateInInventory("CombatKnife");
        player.GetInventory().CreateInInventory("HuntingKnife");
        player.GetInventory().CreateInInventory("Rangefinder");
    }

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		itemClothing = player.FindAttachmentBySlotName( "Body" );
		if ( itemClothing )
		{
			player.RemoveAllItems();
            
            SpawnJeffSetup(player);

            // string playerTypeArray[] = {"Townsperson", "Paramedic", "Hunter", "Industrial", "Hiker", "Backpacker", "Skateboarder"};
            
            int rndIndex = Math.RandomInt( 0, 7 );
            // string playerType = playerTypeArray[rndIndex];

            // switch(playerType) {
            //     case "Townsperson":
            //         setTownspersonStartingItems(player);
            //         break;
            //     case "Paramedic":
            //         setMedicStartingItems(player);
            //         break;
            //     case "Police":
            //         setPoliceStartingItems(player);
            //         break;
            //     case "Hunter":
            //         setHunterStartingItems(player);
            //         break;
            //     case "Industrial":
            //         setIndustrialStartingItems(player);
            //         break;
            //     case "Hiker":
            //         setHikerStartingItems(player);
            //         break;
            //     case "Backpacker":
            //         setBackpackerStartingItems(player);
            //         break;
            //     case "Biker":
            //         setBikerStartingItems(player);
            //         break;
            //     case "EscapedPrisoner":
            //         setEscapedPrisonerStartingItems(player);
            //         break;
            //     case "Skateboarder":
            //         setSkateboarderStartingItems(player);
            //         break;
            //     case "DirtBiker":
            //         setDirtBikerStartingItems(player);
            //         break;
            //     case "Firefighter":
            //         setFirefighterStartingItems(player);
            //         break;
            //     case "Soldier":
            //         setSoldierStartingItems(player);
            //         break;
            //     default:
            //         setTownspersonStartingItems(player);
            //         break;
            // }

            // universal starting items that every type gets
            
            itemEnt = player.GetInventory().CreateInInventory( "BandageDressing" );
			if ( Class.CastTo( itemBs, itemEnt ) )
				itemBs.SetQuantity( 4 );

			rndIndex = Math.RandomInt( 0, 4 );
			itemEnt = player.GetInventory().CreateInInventory( "Chemlight_White" );
            
            itemEnt = player.GetInventory().CreateInInventory( "CanOpener" );
            itemEnt = player.GetInventory().CreateInInventory( "SodaCan_Cola" );
        	itemEnt = player.GetInventory().CreateInInventory( "SodaCan_Spite" );
            itemEnt = player.GetInventory().CreateInInventory( "BakedBeansCan" );
            itemEnt = player.GetInventory().CreateInInventory( "SpaghettiCan" );
		}
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
