#pragma once


struct TestControlsFrame : public uiFrame {
  uiTextEdit * textEdit;
  uiButton * normalButton, * switchButton;
  uiListBox * listBox;
  uiComboBox * comboBox1, * comboBox2;

  TestControlsFrame(uiFrame * parent)
    : uiFrame(parent, "Test Controls", Point(150, 20), Size(420, 240), false) {

    new uiLabel(this, "Text Label:", Point(10,  33));
    textEdit = new uiTextEdit(this, "Text Edit", Point(70,  30), Size(340, 20));
    textEdit->anchors().right = true;

    normalButton = new uiButton(this, "Normal Button", Point(10, 60), Size(80, 20));
    normalButton->onClick = [&]() { app()->messageBox("", "Button Pressed!", "OK", nullptr, nullptr, uiMessageBoxIcon::Info); };

    switchButton = new uiButton(this, "Switch Button OFF", Point(120, 60), Size(100, 20), uiButtonKind::Switch);
    switchButton->onChange = [&]() { switchButton->setText( switchButton->down() ? "Switch Button ON" : "Switch Button OFF" ); };

    listBox = new uiListBox(this, Point(10, 90), Size(150, 80));
    listBox->anchors().right = true;
    listBox->items().append("Listbox Row 0");
    listBox->items().append("Listbox Row 1");
    listBox->items().append("Listbox Row 2");
    listBox->items().append("Listbox Row 3");
    listBox->items().append("Listbox Row 4");
    listBox->items().append("Listbox Row 5");
    listBox->items().append("Listbox Row 6");
    listBox->items().append("Listbox Row 7");

    auto label = new uiLabel(this, "Normal ComboBox:", Point(170, 93));
    label->anchors().left  = false;
    label->anchors().right = true;
    comboBox1 = new uiComboBox(this, Point(270, 90), Size(140, 20), 80);
    comboBox1->anchors().left  = false;
    comboBox1->anchors().right = true;
    comboBox1->items().append("ComboBox Row 0");
    comboBox1->items().append("ComboBox Row 1");
    comboBox1->items().append("ComboBox Row 2");
    comboBox1->items().append("ComboBox Row 3");
    comboBox1->items().append("ComboBox Row 4");
    comboBox1->items().append("ComboBox Row 5");
    comboBox1->items().append("ComboBox Row 6");
    comboBox1->items().append("ComboBox Row 7");
    comboBox1->items().append("ComboBox Row 8");
    comboBox1->items().append("ComboBox Row 9");
    label = new uiLabel(this, "Editable ComboBox:", Point(170, 123));
    label->anchors().left  = false;
    label->anchors().right = true;
    comboBox2 = new uiComboBox(this, Point(270, 120), Size(140, 20), 80);
    comboBox2->comboBoxProps().openOnFocus = false;
    comboBox2->textEditProps().hasCaret  = true;
    comboBox2->textEditProps().allowEdit = true;
    comboBox2->anchors().left  = false;
    comboBox2->anchors().right = true;
    comboBox2->items().copyFrom(comboBox1->items());

  }
};
