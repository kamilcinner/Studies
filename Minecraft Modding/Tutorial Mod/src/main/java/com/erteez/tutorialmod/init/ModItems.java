package com.erteez.tutorialmod.init;

import java.util.ArrayList;
import java.util.List;

import com.erteez.tutorialmod.items.ItemBase;

import net.minecraft.item.Item;

public class ModItems {

	public static final List<Item> ITEMS = new ArrayList<Item>();
	
	// line here, lang, json and texture
	public static final Item RUBY = new ItemBase("ruby");
	public static final Item OBSIDIAN_INGOT = new ItemBase("obsidian_ingot");
	public static final Item POLUB_POLLUB = new ItemBase("polub_pollub");
}
