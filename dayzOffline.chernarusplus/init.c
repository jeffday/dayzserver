void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
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
    
    void setSoldierStartingItems(PlayerBase player)
    {
    	EntityAI itemEnt;
	
	itemEnt = player.GetInventory().CreateInInventory("MMG_camelback_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_Med_Pouch_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_bottle_multicam");
	
	itemEnt = player.GetInventory().CreateInInventory("MMG_operatorshirt_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_combatpants_multicam");
	itemEnt = player.GetInventory().CreateInInventory("mmg_tactical_gloves_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_boots_multicam");
	
	itemEnt = player.GetInventory().CreateInInventory("MMG_tt_Vest_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_ammo_pouch_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_ammo_pouch_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_tactical_pouch_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_Med_Pouch_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_bottle_multicam");
	
	itemEnt = player.GetInventory().CreateInInventory("MMG_falcon_b1_belt_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_tactical_pouch_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_Med_Pouch_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_sheath_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_bottle_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_Holster_multicam");
	
	itemEnt = player.GetInventory().CreateInInventory("MMG_tactical_helmet_multicam");
	itemEnt = player.GetInventory().CreateInInventory("MMG_headphones_green");
	itemEnt = player.GetInventory().CreateInInventory("UniversalLight");
	itemEnt = player.GetInventory().CreateInInventory("MMG_balaclava_multicam");
	
	itemEnt = player.GetInventory().CreateInInventory("CombatKnife");
	itemEnt = player.GetInventory().CreateInInventory("MMG_carbine_grey");
	
	itemEnt = player.GetInventory().CreateInInventory("TTC_HK416Comp");
	itemEnt = player.GetInventory().CreateInInventory("TTC_DMR_VFG");
	itemEnt = player.GetInventory().CreateInInventory("TTC_Elcan");
	itemEnt = player.GetInventory().CreateInInventory("TTC_Universal_Suppressor_BLACK");

	itemEnt = player.GetInventory().CreateInInventory("TTC_DMR_556Pmag_30rnd");
	itemEnt = player.GetInventory().CreateInInventory("TTC_DMR_556Pmag_30rnd");
	
	itemEnt = player.GetInventory().CreateInInventory("TTC_HK417");
	itemEnt = player.GetInventory().CreateInInventory("TTC_ButtstockHK_Black");
	itemEnt = player.GetInventory().CreateInInventory("TTC_DMR_VFG");
	itemEnt = player.GetInventory().CreateInInventory("TTC_VortexSE_Optic");
	itemEnt = player.GetInventory().CreateInInventory("TTC_M14Suppressor");
	
	itemEnt = player.GetInventory().CreateInInventory("TTC_HK417_Magazine_20rnd");
	itemEnt = player.GetInventory().CreateInInventory("TTC_HK417_Magazine_20rnd");
	itemEnt = player.GetInventory().CreateInInventory("TTC_HK417_Magazine_20rnd");
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
        string bag[] = {"TaloonBag_Green", "TaloonBag_Blue", "TaloonBag_Green", "TaloonBag_Orange"};
        
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
    	string head[] = {"Ushanka_Green", "Ushanka_Green", "Ushanka_Black", "Ushanka_Black"}
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
        itemEnt = player.GetInventory().CreateInInventory("HuntingKnife");
        
        string rifles[] = {"CZ527","Mosin9130","Winchester70","TTC_R700","TTC_kar98k","TTC_LeeEnfield", "TTC_M1903", "TTC_MAS36", "TTC_Winchester1873", "B95"};
        string ammoTypes[] = {"Mag_CZ527_5rnd", "Ammo_762x54", "Ammo_308Win", "Ammo_308Win", "TTC_Ammo_8mm", "TTC_Ammo_303", "TTC_Ammo_3006", "Ammo_762x54", "TTC_Ammo_4570", "Ammo_308Win"};
        string scopes[] = {"HuntingOptic", "PUScopeOptic", "HuntingOptic", "HuntingOptic", "HuntingOptic", "PUScopeOptic", "PUScopeOptic", "HuntingOptic", "HuntingOptic", "HuntingOptic"};

        rndIndex = Math.RandomInt( 0, 10 );
        
        itemEnt = SpawnWithRandomHealth(player, rifles[rndIndex]);
        itemEnt = player.GetInventory().CreateInInventory(scopes[rndIndex]);
        itemEnt = player.GetInventory().CreateInInventory(ammoTypes[rndIndex]);

        if (Class.CastTo( itemBs, itemEnt )) {
		itemBs.SetQuantity( 5 );
        }
    }
    
    void setIndustrialStartingItems(PlayerBase player)
    {
    	EntityAI itemEnt;
    
    	string head[] = {"ConstructionHelmet_White","ConstructionHelmet_Lime","ConstructionHelmet_Yellow","ConstructionHelmet_Orange","ConstructionHelmet_Red","ConstructionHelmet_Blue"};
        string torso[] = {"JumpsuitJacket_Gray","JumpsuitJacket_Green","JumpsuitJacket_Gray","JumpsuitJacket_Gray","JumpsuitJacket_Red","JumpsuitJacket_Blue"};
        string legs[] = {"JumpsuitPants_Grey","JumpsuitPants_Green","JumpsuitPants_Grey","JumpsuitPants_Grey","JumpsuitPants_Red","JumpsuitPants_Blue"};
        string bag[] = {"DryBag_Black","DryBag_Green","DryBag_Yellow","DryBag_Orange","DryBag_Red","DryBag_Blue"}
        
        int rndIndex = Math.RandomInt( 0, 6 );
        
        itemEnt = SpawnWithRandomHealth(player, head[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, torso[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, legs[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, bag[rndIndex]);
        
        itemEnt = SpawnWithRandomHealth(player, "ReflexVest");
        itemEnt = SpawnWithRandomHealth(player, "NioshFaceMask");
        itemEnt = SpawnWithRandomHealth(player, "WorkingBoots_Yellow");
        itemEnt = SpawnWithRandomHealth(player, "WorkingGloves_Beige");
        
        string tools[] = {"Wrench","PipeWrench","Hammer","Hacksaw","Handsaw","Shovel"}
        
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
        
        itemEnt = SpawnWithRandomHealth(player, "Glock19");
        itemEnt = player.GetInventory().CreateInInventory("Mag_Glock_15Rnd");
            
        if (Class.CastTo(itemBs, itemEnt)) {
			itemBs.SetQuantity(15);
        }
    }
    
    void setMedicStartingItems(PlayerBase player)
    {
    	string head[] = {"BeanieHat_Red", "BeanieHat_Green", "BeanieHat_Blue"};
        string jackets[] = {"ParamedicJacket_Crimson", "ParamedicJacket_Green", "ParamedicJacket_Blue"};
        string pants[] = {"ParamedicPants_Crimson", "ParamedicPants_Green", "ParamedicPants_Blue"};
        string gloves[] = {"SurgicalGloves_LightBlue", "SurgicalGloves_Green", "SurgicalGloves_Blue"};
     
     	EntityAI itemEnt;
     
        int rndIndex = Math.RandomInt( 0, 3 );
        
        itemEnt = SpawnWithRandomHealth(player, head[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, jackets[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, pants[rndIndex]);
        itemEnt = SpawnWithRandomHealth(player, gloves[rndIndex]);
        
        itemEnt = SpawnWithRandomHealth(player, "WorkingBoots_Brown");
        
        itemEnt = SpawnWithRandomHealth(player, "Flaregun");
        
        string flareColors[] = {"Ammo_Flare","Ammo_FlareBlue","Ammo_FlareGreen","Ammo_FlareRed"}
        rndIndex = Math.RandomInt( 0, 4 );
        
        itemEnt = player.GetInventory().CreateInInventory(flareColors[rndIndex]);
        
        itemEnt = SpawnWithRandomHealth(player, "SurgicalMask");
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
            
            string playerTypeArray[] = {"Townsperson", "Paramedic", "Police", "Hunter", "Industrial", "Hiker", "Backpacker", "Biker", "EscapedPrisoner", "Skateboarder", "DirtBiker", "Firefighter"};
            
            int rndIndex = Math.RandomInt( 0, 12 );
            
//             if (rndIndex == 0) {
//             	setTownspersonStartingItems(player);
//             } else if (rndIndex == 1){
//             	setMedicStartingItems(player);
//             } else if (rndIndex == 2){
//             	setPoliceStartingItems(player);
//             } else if (rndIndex == 3){
//             	setHunterStartingItems(player);
//             } else if (rndIndex == 4){
//             	setIndustrialStartingItems(player);
//             } else if (rndIndex == 5){
//             	setHikerStartingItems(player);
//             } else if (rndIndex == 6) {
//             	setBackpackerStartingItems(player);
//             } else if (rndIndex == 7){
//             	setBikerStartingItems(player);
//             } else if (rndIndex == 8){
//                setEscapedPrisonerStartingItems(player);
//             } else if (rndIndex == 9){
//                 setSkateboarderStartingItems(player);
//             } else if (rndIndex == 10){
//                 setDirtBikerStartingItems(player);
//             } else if (rndIndex == 11){
//                 setFirefighterStartingItems(player);
//             } else {
	    	setSoldierStartingItems(player);
// 	    }

            // universal starting items that every type gets
            
            itemEnt = player.GetInventory().CreateInInventory( "BandageDressing" );
			if ( Class.CastTo( itemBs, itemEnt ) )
				itemBs.SetQuantity( 4 );
            
            string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };

			rndIndex = Math.RandomInt( 0, 4 );
			itemEnt = player.GetInventory().CreateInInventory( chemlightArray[rndIndex] );
            
            itemEnt = player.GetInventory().CreateInInventory( "SodaCan_Cola" );
        	itemEnt = player.GetInventory().CreateInInventory( "SodaCan_Spite" );

			rand = Math.RandomFloatInclusive( 0.0, 1.0 );

			if ( rand < 0.5 )
				itemEnt = player.GetInventory().CreateInInventory( "ZagorkyChocolate" );
			else
				itemEnt = player.GetInventory().CreateInInventory( "ZagorkyPeanuts" );
		}
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
