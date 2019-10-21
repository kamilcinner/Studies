package com.erteez.tutorialmod.init;

import java.util.ArrayList;
import java.util.List;

import com.erteez.tutorialmod.blocks.BlockBase;

import net.minecraft.block.Block;
import net.minecraft.block.material.Material;

public class ModBlocks {

	public static final List<Block> BLOCKS = new ArrayList<Block>();
	
	// line here, 3 jsons, lang and texture
	public static final Block RUBY_BLOCK = new BlockBase("ruby_block", Material.IRON);
	
	
}
