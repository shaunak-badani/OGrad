import '../App.css';
import JobConfig from '../components/JobConfig';

const FrontPage = () => {

  return (
    <>
    <div>
    <div className="min-h-screen p-8 pb-8 sm:p-8">      
      <main className="max-w-4xl mx-auto gap-16">
      <div>
      <h1 className="scroll-m-20 text-4xl font-extrabold tracking-tight lg:text-5xl">
        A lightweight ML framework
      </h1>
      <p className="leading-7 [&:not(:first-child)]:mt-6">
        With an ML framework built in C++, train your neural networks in less time!
      </p>
      </div>
      <JobConfig /> 

      </main>

    </div>
    </div>

      
    </>
  )
}

export default FrontPage
