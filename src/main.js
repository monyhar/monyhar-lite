const { app, BrowserWindow } = require('electron');

init();

async function createWindow() {
    const window = new BrowserWindow({
        width: 1920,
        height: 1080
    });
    window.loadFile('src/index.html');
}

async function init() {
    await app.whenReady();
    await createWindow();
}