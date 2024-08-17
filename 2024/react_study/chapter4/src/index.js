import React from 'react';
import {createRoot} from 'react-dom/client';
import App, {ToolbarApp, GalleryApp, SendFormApp, AddThreeApp, TextFormApp} from './App';
import "./styles.css"

const root = createRoot(document.getElementById('root'));
root.render(
  <React.StrictMode>
    <App />
  </React.StrictMode>
);

const toolbar = createRoot(document.getElementById("toolbar"));
toolbar.render(
  <ToolbarApp />
);

const gallery = createRoot(document.getElementById("gallery"));
gallery.render(
  <GalleryApp />
);

const sendform = createRoot(document.getElementById("sendform"));
sendform.render(
  <SendFormApp />
);

const addThree = createRoot(document.getElementById("addThree"));
addThree.render(
  <AddThreeApp />
);

const textform = createRoot(document.getElementById("textform"));
textform.render(
  <TextFormApp />
)