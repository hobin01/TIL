import React, {StrictMode} from 'react';
import {createRoot} from 'react-dom/client';

import './styles.css';
import App, {SubmitCheckApp, FullnameApp, StateLiftingApp, ChatApp, TaskApp, LevelContextApp, TaskApp2} from './App';

const root = createRoot(document.getElementById('root'));
root.render(
  <StrictMode>
    <App />
  </StrictMode>
);

const submitcheck = createRoot(document.getElementById("submitcheck"));
submitcheck.render(
  <SubmitCheckApp />
);

const fullname = createRoot(document.getElementById("fullname"));
fullname.render(
  <FullnameApp />
);

const statelifting = createRoot(document.getElementById("statelifting"));
statelifting.render(
  <StateLiftingApp />
);

const chat = createRoot(document.getElementById("chat"));
chat.render(
  <ChatApp />
);

const task = createRoot(document.getElementById("task"));
task.render(
  <TaskApp />
);

const levelContext = createRoot(document.getElementById("levelContext"));
levelContext.render(
  <LevelContextApp />
);

const task2 = createRoot(document.getElementById("task2"));
task2.render(
  <TaskApp2 />
);