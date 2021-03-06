#include "MyTexture.h"
#include "MyGame.h"


namespace SPACEYSHOOT
{
  //blend this and other textures and create a new blended texture
  //using the given mask. Note: all textures and the mask must have
  //the same dimension
  MyTexture * MyTexture::blend(MyTexture * other, Uint32 * mask)
  {
    SDL_Renderer * renderer=getMyGame()->getRenderer();
    
    Uint32 * pixels_this =new Uint32[mHeight*mWidth];
    Uint32 * pixels_other=new Uint32[mHeight*mWidth];

    assert(pixels_this && pixels_other);

    //render this image and then read pixels back
    this->render(0,0);
    SDL_RenderReadPixels(renderer,NULL,SDL_PIXELFORMAT_ARGB8888,(void*)pixels_this, sizeof(Uint32)*mWidth);

    //render that image and then read pixels back
    other->render(0,0);
    SDL_RenderReadPixels(renderer,NULL,SDL_PIXELFORMAT_ARGB8888,(void*)pixels_other, sizeof(Uint32)*mWidth);

    Uint32 format = SDL_GetWindowPixelFormat( getMyGame()->getWindow() );
    SDL_PixelFormat* mappingFormat = SDL_AllocFormat( format );

    for(int h=0;h<mHeight;h++)
    {
      for(int w=0;w<mWidth;w++)
      {
        int i=h*mWidth+w;
        float s=(mask[i] & 255)*1.0/255;
        s=3*s*s-2*s*s*s;


        Uint8 ir,ig,ib,ia,o_r,og,ob,oa;
        SDL_GetRGBA(pixels_this[i], mappingFormat,&ir,&ig,&ib,&ia);
        SDL_GetRGBA(pixels_other[i], mappingFormat,&o_r,&og,&ob,&oa);

        Uint8 r=ir+(Uint8)(s*(o_r-ir));
        Uint8 g=ig+(Uint8)(s*(og-ig));
        Uint8 b=ib+(Uint8)(s*(ob-ib));
        Uint8 a=ia+(Uint8)(s*(oa-ia));

        pixels_this[i] = SDL_MapRGBA( mappingFormat, r, g, b, a );
      }
    }


    SDL_FreeFormat( mappingFormat );

    //Loads image from a given buffer
    MyTexture * newtext=new MyTexture();
		newtext->loadFromBuffer( pixels_this, mWidth, mHeight );

    delete [] pixels_this;
    delete [] pixels_other;

    return newtext; //replace this line
  }

  //Loads image from a given buffer
  bool MyTexture::loadFromBuffer( Uint32 * buffer, int width, int height )
  {
    SDL_Texture * texture = SDL_CreateTexture(getMyGame()->getRenderer(),
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
    assert(texture);
    SDL_UpdateTexture(texture, NULL, buffer, width * sizeof(Uint32));

    mWidth = width;
    mHeight = height;

    //Return success
    mTexture = texture;
    return mTexture != NULL;
  }

  bool MyTexture::loadStreamableFromFile( std::string path )
  {
    using namespace std;

  	//Get rid of preexisting texture
  	free();

  	//The final texture
  	SDL_Texture* newTexture = NULL;

  	//Load image at specified path
  	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  	if( loadedSurface == NULL )
  	{
  		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
  	}
  	else
  	{
      SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_GetWindowPixelFormat( getMyGame()->getWindow() ), 0 );
      if( formattedSurface == NULL )
  		{
  			printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
  		}
  		else
  		{
  			//Create blank streamable texture
  			newTexture = SDL_CreateTexture( getMyGame()->getRenderer(), SDL_GetWindowPixelFormat( getMyGame()->getWindow() ), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
  			if( newTexture == NULL )
  			{
  				printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
  			}
  			else
  			{
  				//Lock texture for manipulation
          void * mPixels = NULL;
          int mPitch;
  				SDL_LockTexture( newTexture, NULL, &mPixels, &mPitch );

  				//Copy loaded/formatted surface pixels
  				memcpy( mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

  				//Unlock texture to update
  				SDL_UnlockTexture( newTexture );
  				mPixels = NULL;

  				//Get image dimensions
  				mWidth = formattedSurface->w;
  				mHeight = formattedSurface->h;
  			}

  			//Get rid of old formatted surface
  			SDL_FreeSurface( formattedSurface );
      }

  		//Color key image
  		//SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

  		//Create texture from surface pixels
      //newTexture = SDL_CreateTextureFromSurface( getMyGame()->getRenderer(), loadedSurface );
  		// if( newTexture == NULL )
  		// {
  		// 	printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
  		// }
  		// else
  		// {
  		// 	//Get image dimensions
  		// 	mWidth = loadedSurface->w;
  		// 	mHeight = loadedSurface->h;
  		// }

  		//Get rid of old loaded surface
  		SDL_FreeSurface( loadedSurface );
  	}

  	//Return success
  	mTexture = newTexture;
  	return mTexture != NULL;
  }

  bool MyTexture::loadFromFile( std::string path )
  {
    using namespace std;

  	//Get rid of preexisting texture
  	free();

  	//The final texture
  	SDL_Texture* newTexture = NULL;

  	//Load image at specified path
  	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  	if( loadedSurface == NULL )
  	{
  		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
  	}
  	else
  	{
      //Color key image
      SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

  		//Create texture from surface pixels
      newTexture = SDL_CreateTextureFromSurface( getMyGame()->getRenderer(), loadedSurface );
  		if( newTexture == NULL )
  		{
  			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
  		}
  		else
  		{
  			//Get image dimensions
  			mWidth = loadedSurface->w;
  			mHeight = loadedSurface->h;
  		}

  		//Get rid of old loaded surface
  		SDL_FreeSurface( loadedSurface );
  	}

  	//Return success
  	mTexture = newTexture;
  	return mTexture != NULL;
  }

  void MyTexture::free()
  {
  	//Free texture if it exists
  	if( mTexture != NULL )
  	{
  		SDL_DestroyTexture( mTexture );
  		mTexture = NULL;
  		mWidth = 0;
  		mHeight = 0;
  	}
  }

  void MyTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
  {
  	//Modulate texture rgb
  	SDL_SetTextureColorMod( mTexture, red, green, blue );
  }

  void MyTexture::setBlendMode( SDL_BlendMode blending )
  {
  	//Set blending function
  	SDL_SetTextureBlendMode( mTexture, blending );
  }

  void MyTexture::setAlpha( Uint8 alpha )
  {
  	//Modulate texture alpha
  	SDL_SetTextureAlphaMod( mTexture, alpha );
  }

  void MyTexture::render( int x, int y, SDL_Rect* clip, float scale, float angle,
                          SDL_Point* center, SDL_RendererFlip flip )
  {
  	//Set rendering space and render to screen
  	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

  	//Set clip rendering dimensions
  	if( clip != NULL )
  	{
  		renderQuad.w = static_cast<int>(clip->w*scale);
  		renderQuad.h = static_cast<int>(clip->h*scale);
  	}

  	//Render to screen
  	SDL_RenderCopyEx( getMyGame()->getRenderer(), mTexture, clip, &renderQuad, angle, center, flip );
  }

  int MyTexture::getWidth()
  {
  	return mWidth;
  }

  int MyTexture::getHeight()
  {
  	return mHeight;
  }


}//end namespace GMUCS425
