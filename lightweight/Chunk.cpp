#include "Chunk.h"
#include "Game.h"
#include "World.h"
void Chunk::Update(const double& deltaTime)
{

}

FaceModel* Face::model = nullptr;
void Chunk::GenerateMesh()
{
	 for (size_t x = 0; x < c; x++)
	 {
		  for (size_t y = 0; y < c; y++)
		  {
				for (size_t z = 0; z < c; z++)
				
					 if (blocks[x][y][z])
					 {
						  blocks[x][y][z] = new ChunkBlock();
						  blocks[x][y][z]->position = glm::vec3(position.x*c,0, position.z * c) + glm::vec3(x, y, z);
						  
						  if (x == 0) {
								Chunk* s = Game::GetInstance()->world->GetChunk({position.x-1, position.z});
								if (s)
								{
									 ChunkBlock* b = s->blocks[c - 1][y][z];
									 if (!s->blocks[c - 1][y][z])
										  blocks[x][y][z]->AddFace(new LeftFace());
								}
								else
									 blocks[x][y][z]->AddFace(new LeftFace());
						  }
						  if (x == c - 1) {
								Chunk* s = Game::GetInstance()->world->GetChunk({ position.x + 1, position.z });
								if (s)
								{
									 if (!s->blocks[0][y][z])
										  blocks[x][y][z]->AddFace(new RightFace());
								}
								else
									 blocks[x][y][z]->AddFace(new RightFace());
						  }
						  if (x > 0 && x < c - 1)
						  {
								if (!blocks[x - 1][y][z]) {

									 blocks[x][y][z]->AddFace(new LeftFace());
								}
								if (!blocks[x + 1][y][z]) {

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
								if (!blocks[x][y - 1][z])
								{
									 blocks[x][y][z]->AddFace(new BottomFace());
								}
								if (!blocks[x][y + 1][z])
								{
									 blocks[x][y][z]->AddFace(new TopFace());
								}
						  }
						  if (z == 0) {
								Chunk* s = Game::GetInstance()->world->GetChunk({ position.x, position.z -1});
								if (s)
								{
									 if (!s->blocks[x][y][c-1])
										  blocks[x][y][z]->AddFace(new BackFace());
								}
								else
									 blocks[x][y][z]->AddFace(new BackFace());
						  }

						  if (z == c - 1) 
								{
									 Chunk* s = Game::GetInstance()->world->GetChunk({ position.x, position.z + 1 });
									 if (s)
									 {
										  if (!s->blocks[x][y][0])
												blocks[x][y][z]->AddFace(new FrontFace());
									 }
									 else
										  blocks[x][y][z]->AddFace(new FrontFace());
								}
						  
						  if (z > 0 && z < c - 1) {
								if (!blocks[x][y][z - 1])
								{
									 blocks[x][y][z]->AddFace(new BackFace());
								}
								if (!blocks[x][y][z + 1])
								{
									 blocks[x][y][z]->AddFace(new FrontFace());
								}
						  }

					 
				}
		  }
	 }
}
