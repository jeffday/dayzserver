void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 8, reset_day = 10;
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
                Debug.LogInfo("generated item name: " + prefix + camoType);
                return prefix + "olive";
            }
        }

        Debug.LogInfo("generated item name: " + prefix + camoType);

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

	void SpawnJeffSetup(PlayerBase player) {
        string camoType = "multicam_tropic";
        string spurgleCamo = "WoodlandCamo";

        autoptr TStringArray clothes = {getItemNameForCamoType("MMG_tactical_helmet_", camoType),"ThickFramesGlasses","NioshFaceMask",getItemNameForCamoType("MMG_combatshirt_", camoType),getItemNameForCamoType("mmg_tactical_gloves_", camoType),getItemNameForCamoType("MMG_combatpants_", camoType),"SK8_Sneakers_Black"};

        spawnItemsOnPlayer(player, clothes);

        string bag = "Spur_CamelBag_" + spurgleCamo;
        autoptr TStringArray bagAttachments = {"SmershBag_Spur_" + spurgleCamo,"PlateCarrierHolster_Spur_" + spurgleCamo,"Spur_KnifeSheath_Green","PersonalRadio"};

        spawnItemWithAttachments(player, bag, bagAttachments);

        string belt = getItemNameForCamoType("MMG_falcon_b1_belt_", camoType);
        autoptr TStringArray beltAttachments = {getItemNameForCamoType("MMG_tactical_pouch_", camoType), getItemNameForCamoType("MMG_Med_Pouch_", camoType), getItemNameForCamoType("MMG_sheath_", camoType), getItemNameForCamoType("MMG_Holster_", camoType), getItemNameForCamoType("MMG_bottle_", camoType)};

        spawnItemWithAttachments(player, belt, beltAttachments);

        string vest = getItemNameForCamoType("MMG_tt_Vest_", camoType);
        autoptr TStringArray vestAttachments = {getItemNameForCamoType("MMG_ammo_pouch_", camoType), getItemNameForCamoType("MMG_ammo_pouch_", camoType), getItemNameForCamoType("MMG_tactical_pouch_", camoType), getItemNameForCamoType("MMG_Med_Pouch_", camoType), getItemNameForCamoType("MMG_bottle_", camoType)};

        spawnItemWithAttachments(player, vest, vestAttachments);

        spawnRifle(player, "TTC_MAS36");
        spawnItemNTimesOnPlayer(player, "AmmoBox_762x54_20Rnd", 12);

        spawnSidearm(player);
        player.GetInventory().CreateInInventory("TTC_PistolSuppressor");

        player.GetInventory().CreateInInventory("CombatKnife");
        player.GetInventory().CreateInInventory("HuntingKnife");
        player.GetInventory().CreateInInventory("Rangefinder");
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
            
            SpawnJeffSetup(player);

			itemEnt = player.GetInventory().CreateInInventory( "BandageDressing" );
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