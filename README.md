Content-Aware Image Resizer
===========================
You are an adventurous gold miner. However, in your avarice you’ve ignored several safe-tunneling practices, and a recent earthquake has left you trapped! Luckily, out of paranoia, you always carry ridiculous quantities of dynamite sticks with you. You need to blast your way out and make the most of each dynamite stick by blasting the piles of rubble which take the fewest sticks to destroy.

The mine you are trapped in can be represented with a 2-dimensional grid. There are 2 types of tiles:

Tiles containing rubble: Think of cleared tiles as containing 0 rubble. A tile in the mine could contain 0 before you clear it, that means that it never contained rubble

Tiles containing TNT: All tiles touching the TNT tile are also “cleared”. If a TNT tile is touching another TNT tile, this will cause a chain explosion.

You (the miner) start on a specified tile. At every iteration, you will attempt to blast away the “easiest” tile you can “access”, until you escape!

By Felix Lu <felixlu@umich.edu>
