import { SimpleToolbar } from "./Button";
import Gallery from "./Gallery";
import SendForm from "./SendForm.js";
import AddThree from "./AddThree.js";
import TextForm from "./TextForm.js";
import Clock from "./Clock.js";
import Pointer from "./Pointer.js";
import ArrayUpdate from "./ArrayUpdate.js";

export default function App() {
  return <div></div>;
}

export function ToolbarApp() {
  return (
    <>
      <h2>click event test</h2>
      <SimpleToolbar />
    </>
  );
}

export function GalleryApp() {
  return (
    <>
      <h2>Sculpture Gallery</h2>
      <Gallery />
    </>
  );
}

export function SendFormApp() {
  return (
    <>
      <h2>Send Test</h2>
      <SendForm />
    </>
  )
}

export function AddThreeApp() {
  return (
    <>
      <h2>Add 3</h2>
      <AddThree />
    </>
  )
}

export function TextFormApp() {
  return (
    <>
      <h2>text form</h2>
      <TextForm />
    </>
  )
}

export function ClockApp() {
  return (
    <Clock />
  );
}

export function PointerApp() {
  return (
    <Pointer />
  );
}

export function ArrayUpdateApp() {
  return (
    <ArrayUpdate />
  )
}