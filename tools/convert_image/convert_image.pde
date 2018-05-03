/*
* Copyright (c) 2018 letsplentendo
*
* This program is free software; you can redistribute it and/or modify it
* under the terms and conditions of the GNU General Public License,
* version 2, as published by the Free Software Foundation.
*
* This program is distributed in the hope it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

PImage img;
Boolean ready = false;
int i;

void setup() {
  //set the size of your image here.
  size(720, 1280);
  selectInput("Please select an image: ", "fileSelected");
}

void draw() {
  if (img != null && ready == false) {
    ready = true;
    background(255);
    if (img.width > img.height) {
      translate(width / 2, height / 2);
      rotate(-HALF_PI);
      imageMode(CENTER);
      image(img, 0, 0, height, width);
    } else {
      image(img, 0, 0, width, height);
    }
    thread("createFile");
    delay(10);
  }

  if (ready == true) {
    background(255);
    if (img.width > img.height) {
      translate(width / 2, height / 2);
      rotate(-HALF_PI);
      imageMode(CENTER);
      image(img, 0, 0, height, width);
      rotate(HALF_PI);
      translate(-width / 2, -height / 2);
    } else {
      image(img, 0, 0, width, height);
    }
    noStroke();
    float prog = (float) i / (width * height) * height;
    rect(0, prog, width, height - prog);
  }
}

void fileSelected(File selection) {
  if (selection == null) {
    exit();
  } else {
    println("User selected " + selection.getAbsolutePath());
    img = loadImage(selection.getAbsolutePath());
  }
}

void createFile() {
    loadPixels();
    PrintWriter output = createWriter("image.txt");
    String tx = width + "";// + "\n" + height + "\n";
    for (i = 0; i < pixels.length; i++) {
      if (i % width == 0) {
        output.println(tx);
        tx = "";
      }
      String red = pad(hex(int(red(pixels[i])), 2));
      String green = pad(hex(int(green(pixels[i])), 2));
      String blue = pad(hex(int(blue(pixels[i])), 2));
      tx = tx + blue + green + red;
    }
    output.println(tx);
    output.flush();
    output.close();
}

String pad(String in) {
  if (in.length() == 2) {
    return in;
  } else if (in.length() == 1) {
    return "0" + in;
  } else {
    return "00";
  }
}
