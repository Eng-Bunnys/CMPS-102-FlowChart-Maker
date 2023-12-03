void Output::CreateDesignToolBar()
{
    UI.AppMode = DESIGN;    // Design Mode

    // Prepare images for each menu item
    string MenuItemImages[DSN_ITM_CNT];
    MenuItemImages[ITM_VALUE_ASSIGN] = "images\\Assign.jpg";
    MenuItemImages[ITM_COND] = "images\\Condition.jpg";
    MenuItemImages[ITM_EXIT] = "images\\Exit.jpg";

    // Draw menu items
    for (int i = 0; i < DSN_ITM_CNT; i++)
        pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

    // Draw a line under the toolbar
    pWind->SetPen(RED, 2);
    pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

    // Additional code for new items (you can customize the positions):
    pWind->DrawImage("images\\Start.jpg", 3 * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
    pWind->DrawImage("images\\End.jpg", 4 * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
    pWind->DrawImage("images\\Read.jpg", 5 * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
    pWind->DrawImage("images\\Write.jpg", 6 * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
    pWind->DrawImage("images\\Connector.jpg", 7 * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
    // Add more items as needed

    // Draw labels for each item (you can customize the positions and text):
    DrawString(0, UI.ToolBarHeight, "Value Assign");
    DrawString(UI.MenuItemWidth, UI.ToolBarHeight, "Condition");
    DrawString(3 * UI.MenuItemWidth, UI.ToolBarHeight, "Start");
    DrawString(4 * UI.MenuItemWidth, UI.ToolBarHeight, "End");
    DrawString(5 * UI.MenuItemWidth, UI.ToolBarHeight, "Read");
    DrawString(6 * UI.MenuItemWidth, UI.ToolBarHeight, "Write");
    DrawString(7 * UI.MenuItemWidth, UI.ToolBarHeight, "Connector");
    // Add more labels as needed
}
