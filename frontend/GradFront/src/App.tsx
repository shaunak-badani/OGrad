import './App.css';
import { Routes, Route } from 'react-router';
import FrontPage from './pages/FrontPage';
import Tasks from './pages/Tasks';

function App() {

  return (
    <>
      <div className="header p-6 text-xl border-b">Macrograd</div>
      <Routes>
        <Route index element = {<FrontPage />} />
        <Route path="/tasks" element={<Tasks />} />
      </Routes>
    </>
  )
}

export default App
