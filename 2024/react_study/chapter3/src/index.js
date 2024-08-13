import React, {StrictMode} from "react";
import {createRoot} from "react-dom/client";
import "./styles.css";
import App, {DateApp, TimeApp} from "./App";

const root = createRoot(document.getElementById("root"));
root.render(
    <StrictMode>
        <App />
    </StrictMode>
);

const submitBtn = document.getElementById("submit-btn");
submitBtn.addEventListener("click", () => {
    const langInput = document.getElementById("lang").value;
    const datetime = createRoot(document.getElementById("datetime"));
    datetime.render(
        <DateApp lang={langInput} />
    );
});

const currentTime = createRoot(document.getElementById("current-time"));
currentTime.render(
    <TimeApp />
);