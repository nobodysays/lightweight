#include "Chunk.h"

void Chunk::Update()
{
	 for (size_t x = 0; x < c; x++)
	 {
		  for (size_t y = 0; y < c; y++)
		  {
				for (size_t z = 0; z < c; z++)
				{
					 blocks[x][y][z]->Draw();
				}
		  }
	 }
}

FaceModel* Face::model = nullptr;
void Chunk::GenerateMesh()
{
	 for (size_t x = 0; x < c; x++)
	 {
		  for (size_t y = 0; y < c; y++)
		  {
				for (size_t z = 0; z < c; z++)
				{
					 blocks[x][y][z] = new ChunkBlock();
					 blocks[x][y][z]->position = { x, y, z };
					 if (x == 0) {
						  blocks[x][y][z]->AddFace(new LeftFace());
					 }
					 if (x == c-1) {
						  blocks[x][y][z]->AddFace(new RightFace());
					 }
					 if(x>0 && x<c-1)
					 {
						  if (blockIDs[x - 1][y][z] == AIR) {

								blocks[x][y][z]->AddFace(new LeftFace());
						  }
						  if (blockIDs[x + 1][y][z] == AIR) {

								blocks[x][y][z]->AddFace(new RightFace());
						  }
					 }
					 if (y == 0) {
						  blocks[x][y][z]->AddFace(new BottomFace());
					 }
					 if (y == c - 1) {
						  blocks[x][y][z]->AddFace(new TopFace());
					 }
					 if (y > 0 && y < c - 1) {
						  if (blockIDs[x][y - 1][z] == AIR)
						  {
								blocks[x][y][z]->AddFace(new BottomFace());
						  }
						  if (blockIDs[x][y + 1][z] == AIR)
						  {
								blocks[x][y][z]->AddFace(new TopFace());
						  }
					 }
					 if (z == 0) {
						  {
								blocks[x][y][z]->AddFace(new BackFace());
						  }
					 }

					 if (z == c - 1) {
						  {
								blocks[x][y][z]->AddFace(new FrontFace());
						  }
					 }
					 if (z > 0 && z < c - 1)  {
						  if (blockIDs[x][y][z - 1] == AIR)
						  {
								blocks[x][y][z]->AddFace(new BackFace());
						  }
						  if (blockIDs[x][y][z + 1] == AIR)
						  {
								blocks[x][y][z]->AddFace(new FrontFace());
						  }
					 }


				}
		  }
	 }
}
