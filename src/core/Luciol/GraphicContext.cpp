#include <Arduino.h>
#include <NeoPixelBus.h>
#include <math.h>

#include "GraphicContext.h"


GraphicContext::GraphicContext(uint16_t w, uint16_t h) {
  pixels = new RgbColor[w * h];
  width = w;
  height = h;
}


GraphicContext::~GraphicContext() {
  delete pixels;
}


uint16_t GraphicContext::getWidth() {
  return width;
}


uint16_t GraphicContext::getHeight() {
  return height;
}


GraphicContext* GraphicContext::setPixel(int16_t x, int16_t y, RgbColor color) {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    return this;
  }
  if (y & 1) {
    x = width - 1 - x;
  }
  pixels[x + y * width] = gamma.Correct(color);
  return this;
}


GraphicContext* GraphicContext::plot(int16_t x, int16_t y) {
  return setPixel(x, y, drawColor);
}


RgbColor GraphicContext::getPixel(int16_t x, int16_t y) {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    return RgbColor(0, 0, 0);
  }
  return pixels[x + y * width];
}


GraphicContext* GraphicContext::horizontalLine(int16_t y) {
  for (int16_t x=0 ; x<width; x++) {
		this->setPixel(x, y, drawColor);
	}
  return this;
}


GraphicContext* GraphicContext::horizontalLine(int16_t y, RgbColor color) {
  for (int16_t x=0 ; x<width; x++) {
		this->setPixel(x, y, color);
	}
  return this;
}


GraphicContext* GraphicContext::horizontalLine(int16_t x1, int16_t x2, int16_t y) {
  for (int16_t x=x1 ; x<=x2 ; x++) {
		this->setPixel(x, y, drawColor);
	}
  return this;
}


GraphicContext* GraphicContext::verticalLine(int16_t x) {
  for (int16_t y=0 ; y<height ; y++) {
    plot(x, y);
  }
  return this;
}


GraphicContext* GraphicContext::verticalLine(int16_t x, RgbColor color) {
  for (int16_t y=0 ; y<height ; y++) {
    this->setPixel(x, y, color);
  }
  return this;
}


GraphicContext* GraphicContext::verticalLine(int16_t x, int16_t y1, int16_t y2) {
  for (int16_t y=y1 ; y<=y2 ; y++) {
    this->setPixel(x, y, drawColor);
  }
  return this;
}


GraphicContext* GraphicContext::rectangle(int16_t x, int16_t y, int16_t w, int16_t h) {
  for (int16_t i=x; i < x+w; i++) {
    this->plot(i, y)->plot(i, y+h);
  }
  for (int16_t i=y; i < y+h; i++) {
    this->plot(x, i)->plot(x+w, i);
  }
  return this;
}


GraphicContext* GraphicContext::setFillColor(RgbColor color) {
  fillColor = color;
  return this;
}


GraphicContext* GraphicContext::setDrawColor(RgbColor color) {
  drawColor = color;
  return this;
}


GraphicContext* GraphicContext::setColor(RgbColor color) {
  drawColor = color;
  return this;
}


GraphicContext* GraphicContext::fill() {
  for (int16_t y=0 ; y<height ; y++) {
    for (int16_t x=0 ; x<width ; x++) {
      this->setPixel(x, y, fillColor);
    }
  }
  return this;
}


GraphicContext* GraphicContext::clear() {
  RgbColor clearColor(0, 0, 0);
  for (int16_t y=0 ; y<height ; y++) {
    for (int16_t x=0 ; x<width ; x++) {
      this->setPixel(x, y, clearColor);
    }
  }
  return this;
}


GraphicContext* GraphicContext::verticalGradient(RgbColor from, RgbColor to) {
  double step = 1.0 / height;
  float progress = 0;
  for (uint16_t y=0; y<height; y++) {
      horizontalLine(y, RgbColor::LinearBlend(from, to, progress));
      progress += step;
  }
}


GraphicContext* GraphicContext::copy(int16_t srcX, int16_t srcY, int16_t width, int16_t height, GraphicContext* dstGC, int16_t dstX, int16_t dstY) {
  for (int16_t x=0 ; x<width ; x++) {
  		for (int16_t y=0 ; y<height ; y++) {
  			dstGC->setPixel(dstX + x, dstY + y, getPixel(srcX + x, srcY + y));
  		}
  	}
  return this;
}


#ifdef DEVICE_TEBBLE

  #include "fonts/FontManager.h"

  FontManager* fm = FontManager::get();


  GraphicContext* GraphicContext::setFont(String fontName) {
    font = fm->getFont(fontName);
    return this;
  }


  uint16_t GraphicContext::drawChar(int16_t x, int16_t y, char c) {
    uint8_t* ch = font->getChar(c);

    if (ch != NULL) {
      uint16_t h  = font->getHeight();
      uint16_t cw = font->getCharWidth(c);

      for (uint16_t l=0; l<h; l++) {
        uint16_t def = ch[l];
        for (uint16_t b=0; b<cw; b++) {
          if (def & (1<<b)) {
            plot(x + cw - 1 - b, y + l);
          }
        }
      }

      return cw;
    }
    return 0;
  }


  GraphicContext* GraphicContext::text(int16_t x, int16_t y, String text) {
    uint16_t h  = font->getHeight();
    for (uint16_t i=0; i<text.length(); i++) {
      char c = text.charAt(i);
      uint16_t cw = font->getCharWidth(c);
      if ((x > -cw) && (x < width) && (y > -h) && (y < height)) {
        drawChar(x, y, c);
      }
      x += cw + 1;
    }
  }


  uint16_t GraphicContext::getTextWidth(String text) {
    uint16_t width = 0;
    for (uint16_t i=0; i<text.length(); i++) {
      width += font->getCharWidth(text.charAt(i)) + 1;
    }
    return width;
  }


  GraphicContext* GraphicContext::drawBitMask(int16_t x, int16_t y, uint8_t* mask, uint8_t w, uint8_t h) {
      for (uint8_t yi=0; yi<h; yi++) {
        uint8_t def = mask[yi];
        for (uint8_t xi=0; xi<w; xi++) {
          if (def & (1<<xi)) {
            plot(x + w - 1 - xi, y + yi);
          }
        }
      }
      return this;
  }


  uint8_t GraphicContext::getBitMaskMaxWidth(uint8_t* mask, uint8_t h) {
      uint8_t max = 0;
      for (uint8_t l = 0; l < h; l++) {
        uint8_t def = mask[l];
        for (uint8_t b = 0; b < 8; b++) {
          if (def & (1 << b)) {
            if (b > max) {
              max = b;
            }
          }
        }
      }
      return max + 1;
  }

#endif


#ifdef DEVICE_LUCIOL

  GraphicContext* GraphicContext::setPixel(int16_t y, RgbColor color) {
    if (y >= 0 && y < 72) {
      int16_t l1 = y;
      int16_t l2 = 144 -1 - y;
      pixels[l1] = gamma.Correct(color);
      pixels[l2] = gamma.Correct(color);
    }

    return this;
  }


  GraphicContext* GraphicContext::setBlockPixel(int16_t y, RgbColor color) {
    if (y >= 0 && y < 18) {
      int16_t l1 = y*4;
      int16_t l2 = 144 -1 - y*4;
      color = gamma.Correct(color);
      pixels[l1] = color;
      pixels[l1+1] = color;
      pixels[l1+2] = color;
      pixels[l1+3] = color;

      pixels[l2] = color;
      pixels[l2-1] = color;
      pixels[l2-2] = color;
      pixels[l2-3] = color;
    }

    return this;
  }

#endif