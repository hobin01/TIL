import SubmitCheck from "./SubmitCheck";
import Fullname from "./Fullname";
import StateLifting from "./StateLifting";
import Chat from "./chat/Chat";
import TaskMain from "./reducer/TaskMain";
import Page from "./levelContext/Page"
import TaskMain2 from "./reducerContext/TaskMain";

export default function App() {
  return <></>
}

export function SubmitCheckApp() {
  return <SubmitCheck />
}

export function FullnameApp() {
  return <Fullname />
}

export function StateLiftingApp() {
  return <StateLifting />
}

export function ChatApp() {
  return <Chat />
}

export function TaskApp() {
  return <TaskMain />
}

export function LevelContextApp() {
  return <Page />
}

export function TaskApp2() {
  return <TaskMain2 />
}