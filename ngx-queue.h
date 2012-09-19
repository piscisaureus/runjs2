  


<!DOCTYPE html>
<html>
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# githubog: http://ogp.me/ns/fb/githubog#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>libuv/include/uv-private/ngx-queue.h at master · joyent/libuv · GitHub</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub" />
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub" />
    <link rel="apple-touch-icon-precomposed" sizes="57x57" href="apple-touch-icon-114.png" />
    <link rel="apple-touch-icon-precomposed" sizes="114x114" href="apple-touch-icon-114.png" />
    <link rel="apple-touch-icon-precomposed" sizes="72x72" href="apple-touch-icon-144.png" />
    <link rel="apple-touch-icon-precomposed" sizes="144x144" href="apple-touch-icon-144.png" />

    
    
    <link rel="icon" type="image/x-icon" href="/favicon.png" />

    <meta content="authenticity_token" name="csrf-param" />
<meta content="gNLojJVgSXuI4j7wAOYDnYKmgyLTNG4kSCpro4w7bU0=" name="csrf-token" />

    <link href="https://a248.e.akamai.net/assets.github.com/assets/github-6f96eda30ff1556bf501fd7c2915aa0157322687.css" media="screen" rel="stylesheet" type="text/css" />
    <link href="https://a248.e.akamai.net/assets.github.com/assets/github2-c6eeca9bdc855924123b0b9533f2ebe538f56027.css" media="screen" rel="stylesheet" type="text/css" />
    


    <script src="https://a248.e.akamai.net/assets.github.com/assets/frameworks-6f842b2765e7d98b7e93cadc2a364b831cfae37e.js" type="text/javascript"></script>
    <script defer="defer" src="https://a248.e.akamai.net/assets.github.com/assets/github-68a67b35cf28b4535754cc12a5c953951c570a50.js" type="text/javascript"></script>
    
    

      <link rel='permalink' href='/joyent/libuv/blob/ea8db64559680b589196b1ae01152c35d2232c41/include/uv-private/ngx-queue.h'>
    <meta property="og:title" content="libuv"/>
    <meta property="og:type" content="githubog:gitrepository"/>
    <meta property="og:url" content="https://github.com/joyent/libuv"/>
    <meta property="og:image" content="https://a248.e.akamai.net/assets.github.com/images/gravatars/gravatar-user-420.png?1345673561"/>
    <meta property="og:site_name" content="GitHub"/>
    <meta property="og:description" content="platform layer for node.js. Contribute to libuv development by creating an account on GitHub."/>

    <meta name="description" content="platform layer for node.js. Contribute to libuv development by creating an account on GitHub." />
  <link href="https://github.com/joyent/libuv/commits/master.atom" rel="alternate" title="Recent Commits to libuv:master" type="application/atom+xml" />

  </head>


  <body class="logged_out page-blob  vis-public env-production ">
    <div id="wrapper">

    
    

      <div id="header" class="true clearfix">
        <div class="container clearfix">
          <a class="site-logo " href="https://github.com/">
            <img alt="GitHub" class="github-logo-4x" height="30" src="https://a248.e.akamai.net/assets.github.com/images/modules/header/logov7@4x.png?1337118065" />
            <img alt="GitHub" class="github-logo-4x-hover" height="30" src="https://a248.e.akamai.net/assets.github.com/images/modules/header/logov7@4x-hover.png?1337118065" />
          </a>


                  <!--
      make sure to use fully qualified URLs here since this nav
      is used on error pages on other domains
    -->
    <ul class="top-nav logged_out">
        <li class="pricing"><a href="https://github.com/plans">Signup and Pricing</a></li>
        <li class="explore"><a href="https://github.com/explore">Explore GitHub</a></li>
      <li class="features"><a href="https://github.com/features">Features</a></li>
        <li class="blog"><a href="https://github.com/blog">Blog</a></li>
      <li class="login"><a href="https://github.com/login?return_to=%2Fjoyent%2Flibuv%2Fblob%2Fmaster%2Finclude%2Fuv-private%2Fngx-queue.h">Sign in</a></li>
    </ul>



          
        </div>
      </div>

      

      

            <div class="site hfeed" itemscope itemtype="http://schema.org/WebPage">
      <div class="container hentry">
        
        <div class="pagehead repohead instapaper_ignore readability-menu">
        <div class="title-actions-bar">
          


              <ul class="pagehead-actions">


          <li>
            <span class="star-button"><a href="/login?return_to=%2Fjoyent%2Flibuv" class="minibutton js-toggler-target entice tooltipped leftwards" title="You must be signed in to use this feature" rel="nofollow"><span class="mini-icon mini-icon-star"></span>Star</a><a class="social-count js-social-count" href="/joyent/libuv/stargazers">895</a></span>
          </li>
          <li>
            <a href="/login?return_to=%2Fjoyent%2Flibuv" class="minibutton js-toggler-target fork-button entice tooltipped leftwards"  title="You must be signed in to fork a repository" rel="nofollow"><span class="mini-icon mini-icon-fork"></span>Fork</a><a href="/joyent/libuv/network" class="social-count">160</a>
          </li>
    </ul>

          <h1 itemscope itemtype="http://data-vocabulary.org/Breadcrumb" class="entry-title public">
            <span class="repo-label"><span>public</span></span>
            <span class="mega-icon mega-icon-public-repo"></span>
            <span class="author vcard">
              <a href="/joyent" class="url fn" itemprop="url" rel="author">
              <span itemprop="title">joyent</span>
              </a></span> /
            <strong><a href="/joyent/libuv" class="js-current-repository">libuv</a></strong>
          </h1>
        </div>

          

  <ul class="tabs">
    <li><a href="/joyent/libuv" class="selected" highlight="repo_sourcerepo_downloadsrepo_commitsrepo_tagsrepo_branches">Code</a></li>
    <li><a href="/joyent/libuv/network" highlight="repo_network">Network</a></li>
    <li><a href="/joyent/libuv/pulls" highlight="repo_pulls">Pull Requests <span class='counter'>21</span></a></li>

      <li><a href="/joyent/libuv/issues" highlight="repo_issues">Issues <span class='counter'>102</span></a></li>

      <li><a href="/joyent/libuv/wiki" highlight="repo_wiki">Wiki</a></li>


    <li><a href="/joyent/libuv/graphs" highlight="repo_graphsrepo_contributors">Graphs</a></li>


  </ul>
  
<div class="frame frame-center tree-finder" style="display:none"
      data-tree-list-url="/joyent/libuv/tree-list/ea8db64559680b589196b1ae01152c35d2232c41"
      data-blob-url-prefix="/joyent/libuv/blob/ea8db64559680b589196b1ae01152c35d2232c41"
    >

  <div class="breadcrumb">
    <span class="bold"><a href="/joyent/libuv">libuv</a></span> /
    <input class="tree-finder-input js-navigation-enable" type="text" name="query" autocomplete="off" spellcheck="false">
  </div>

    <div class="octotip">
      <p>
        <a href="/joyent/libuv/dismiss-tree-finder-help" class="dismiss js-dismiss-tree-list-help" title="Hide this notice forever" rel="nofollow">Dismiss</a>
        <span class="bold">Octotip:</span> You've activated the <em>file finder</em>
        by pressing <span class="kbd">t</span> Start typing to filter the
        file list. Use <span class="kbd badmono">↑</span> and
        <span class="kbd badmono">↓</span> to navigate,
        <span class="kbd">enter</span> to view files.
      </p>
    </div>

  <table class="tree-browser" cellpadding="0" cellspacing="0">
    <tr class="js-header"><th>&nbsp;</th><th>name</th></tr>
    <tr class="js-no-results no-results" style="display: none">
      <th colspan="2">No matching files</th>
    </tr>
    <tbody class="js-results-list js-navigation-container">
    </tbody>
  </table>
</div>

<div id="jump-to-line" style="display:none">
  <h2>Jump to Line</h2>
  <form accept-charset="UTF-8">
    <input class="textfield" type="text">
    <div class="full-button">
      <button type="submit" class="classy">
        Go
      </button>
    </div>
  </form>
</div>


<div class="tabnav">

  <span class="tabnav-right">
    <ul class="tabnav-tabs">
      <li><a href="/joyent/libuv/tags" class="tabnav-tab" highlight="repo_tags">Tags <span class="counter ">28</span></a></li>
      <li><a href="/joyent/libuv/downloads" class="tabnav-tab" highlight="repo_downloads">Downloads <span class="counter blank">0</span></a></li>
    </ul>
    
  </span>

  <div class="tabnav-widget scope">

    <div class="context-menu-container js-menu-container js-context-menu">
      <a href="#"
         class="minibutton bigger switcher js-menu-target js-commitish-button btn-branch repo-tree"
         data-hotkey="w"
         data-master-branch="master"
         data-ref="master">
         <span><em class="mini-icon mini-icon-branch"></em><i>branch:</i> master</span>
      </a>

      <div class="context-pane commitish-context js-menu-content">
        <a href="javascript:;" class="close js-menu-close"><span class="mini-icon mini-icon-remove-close"></span></a>
        <div class="context-title">Switch branches/tags</div>
        <div class="context-body pane-selector commitish-selector js-navigation-container">
          <div class="filterbar">
            <input type="text" id="context-commitish-filter-field" class="js-navigation-enable" placeholder="Filter branches/tags" data-filterable />
            <ul class="tabs">
              <li><a href="#" data-filter="branches" class="selected">Branches</a></li>
              <li><a href="#" data-filter="tags">Tags</a></li>
            </ul>
          </div>

          <div class="js-filter-tab js-filter-branches" data-filterable-for="context-commitish-filter-field" data-filterable-type=substring>
            <div class="no-results js-not-filterable">Nothing to show</div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/blocking-pipes/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="blocking-pipes" rel="nofollow">blocking-pipes</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/c-ares/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="c-ares" rel="nofollow">c-ares</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/dlopen/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="dlopen" rel="nofollow">dlopen</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/emfile_trick/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="emfile_trick" rel="nofollow">emfile_trick</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/file_watcher/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="file_watcher" rel="nofollow">file_watcher</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/fs/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="fs" rel="nofollow">fs</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/fs_link/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="fs_link" rel="nofollow">fs_link</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/funnel/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="funnel" rel="nofollow">funnel</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/gyp/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="gyp" rel="nofollow">gyp</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/half-duplex-pipes/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="half-duplex-pipes" rel="nofollow">half-duplex-pipes</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/ipc/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="ipc" rel="nofollow">ipc</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/ipc-listen/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="ipc-listen" rel="nofollow">ipc-listen</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/ipc2/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="ipc2" rel="nofollow">ipc2</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/ipc_threads/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="ipc_threads" rel="nofollow">ipc_threads</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/many_accepts/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="many_accepts" rel="nofollow">many_accepts</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target selected">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/master/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="master" rel="nofollow">master</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/merge/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="merge" rel="nofollow">merge</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/multiplicity/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="multiplicity" rel="nofollow">multiplicity</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/multiplicity3/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="multiplicity3" rel="nofollow">multiplicity3</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/next-tick/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="next-tick" rel="nofollow">next-tick</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/noinit/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="noinit" rel="nofollow">noinit</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/platform_api/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="platform_api" rel="nofollow">platform_api</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/poll/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="poll" rel="nofollow">poll</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/pound-fixes/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="pound-fixes" rel="nofollow">pound-fixes</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/prefork/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="prefork" rel="nofollow">prefork</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/refcount/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="refcount" rel="nofollow">refcount</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/report-execve-error/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="report-execve-error" rel="nofollow">report-execve-error</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/spawn-err-async/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="spawn-err-async" rel="nofollow">spawn-err-async</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/spawn_sync/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="spawn_sync" rel="nofollow">spawn_sync</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/spawnext/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="spawnext" rel="nofollow">spawnext</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/stat-regress/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="stat-regress" rel="nofollow">stat-regress</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/stdio/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="stdio" rel="nofollow">stdio</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/structerr/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="structerr" rel="nofollow">structerr</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/tcp-accept-bench/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="tcp-accept-bench" rel="nofollow">tcp-accept-bench</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/travis-debug/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="travis-debug" rel="nofollow">travis-debug</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/uv_kill/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="uv_kill" rel="nofollow">uv_kill</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/v0.6/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="v0.6" rel="nofollow">v0.6</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/v0.7.8-release/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="v0.7.8-release" rel="nofollow">v0.7.8-release</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/v0.8/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="v0.8" rel="nofollow">v0.8</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/versioning/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="versioning" rel="nofollow">versioning</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/win-dns-fix/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="win-dns-fix" rel="nofollow">win-dns-fix</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/win-signals-wip/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="win-signals-wip" rel="nofollow">win-signals-wip</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/win-udp/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="win-udp" rel="nofollow">win-udp</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/win32rw/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="win32rw" rel="nofollow">win32rw</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/windows-many-accepts/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="windows-many-accepts" rel="nofollow">windows-many-accepts</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/writeorder/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="writeorder" rel="nofollow">writeorder</a>
                </h4>
              </div>
              <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/zero_reads/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="zero_reads" rel="nofollow">zero_reads</a>
                </h4>
              </div>
          </div>

          <div class="js-filter-tab js-filter-tags" style="display:none" data-filterable-for="context-commitish-filter-field" data-filterable-type=substring>
            <div class="no-results js-not-filterable">Nothing to show</div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.9.1/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.9.1" rel="nofollow">node-v0.9.1</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.9.0/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.9.0" rel="nofollow">node-v0.9.0</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.8.9/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.8.9" rel="nofollow">node-v0.8.9</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.8.7/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.8.7" rel="nofollow">node-v0.8.7</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.8.6/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.8.6" rel="nofollow">node-v0.8.6</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.8.5/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.8.5" rel="nofollow">node-v0.8.5</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.8.3/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.8.3" rel="nofollow">node-v0.8.3</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.8.2/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.8.2" rel="nofollow">node-v0.8.2</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.8.1/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.8.1" rel="nofollow">node-v0.8.1</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.8.0/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.8.0" rel="nofollow">node-v0.8.0</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.7.12/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.7.12" rel="nofollow">node-v0.7.12</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.7.11/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.7.11" rel="nofollow">node-v0.7.11</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.7.10/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.7.10" rel="nofollow">node-v0.7.10</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.7.9/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.7.9" rel="nofollow">node-v0.7.9</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.7.8/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.7.8" rel="nofollow">node-v0.7.8</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.7.6/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.7.6" rel="nofollow">node-v0.7.6</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.7.4/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.7.4" rel="nofollow">node-v0.7.4</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.7.2/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.7.2" rel="nofollow">node-v0.7.2</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.6.21/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.6.21" rel="nofollow">node-v0.6.21</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.6.19/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.6.19" rel="nofollow">node-v0.6.19</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.6.18/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.6.18" rel="nofollow">node-v0.6.18</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.6.17/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.6.17" rel="nofollow">node-v0.6.17</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.6.16/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.6.16" rel="nofollow">node-v0.6.16</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.6.15/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.6.15" rel="nofollow">node-v0.6.15</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.6.14/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.6.14" rel="nofollow">node-v0.6.14</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.6.13/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.6.13" rel="nofollow">node-v0.6.13</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.6.12/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.6.12" rel="nofollow">node-v0.6.12</a>
                </h4>
              </div>
              <div class="commitish-item tag-commitish selector-item js-navigation-item js-navigation-target ">
                <span class="mini-icon mini-icon-confirm"></span>
                <h4>
                    <a href="/joyent/libuv/blob/node-v0.6.11/include/uv-private/ngx-queue.h" class="js-navigation-open" data-name="node-v0.6.11" rel="nofollow">node-v0.6.11</a>
                </h4>
              </div>
          </div>
        </div>
      </div><!-- /.commitish-context-context -->
    </div>
  </div> <!-- /.scope -->

  <ul class="tabnav-tabs">
    <li><a href="/joyent/libuv" class="selected tabnav-tab" highlight="repo_source">Files</a></li>
    <li><a href="/joyent/libuv/commits/master" class="tabnav-tab" highlight="repo_commits">Commits</a></li>
    <li><a href="/joyent/libuv/branches" class="tabnav-tab" highlight="repo_branches" rel="nofollow">Branches <span class="counter ">47</span></a></li>
  </ul>

</div>

  
  
  


          

        </div><!-- /.repohead -->

        <div id="js-repo-pjax-container" data-pjax-container>
          


<!-- blob contrib key: blob_contributors:v21:a93031afacf73eec931f9a26c323a3bd -->
<!-- blob contrib frag key: views10/v8/blob_contributors:v21:a93031afacf73eec931f9a26c323a3bd -->

<!-- block_view_fragment_key: views10/v8/blob:v21:e53869d56a6a52b7086d34decac377cf -->

  <div id="slider">

    <div class="breadcrumb" data-path="include/uv-private/ngx-queue.h/">
      <b itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/joyent/libuv/tree/ea8db64559680b589196b1ae01152c35d2232c41" class="js-rewrite-sha" itemprop="url"><span itemprop="title">libuv</span></a></b> / <span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/joyent/libuv/tree/ea8db64559680b589196b1ae01152c35d2232c41/include" class="js-rewrite-sha" itemscope="url"><span itemprop="title">include</span></a></span> / <span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/joyent/libuv/tree/ea8db64559680b589196b1ae01152c35d2232c41/include/uv-private" class="js-rewrite-sha" itemscope="url"><span itemprop="title">uv-private</span></a></span> / <strong class="final-path">ngx-queue.h</strong> <span class="js-clippy mini-icon mini-icon-clippy " data-clipboard-text="include/uv-private/ngx-queue.h" data-copied-hint="copied!" data-copy-hint="copy to clipboard"></span>
    </div>

      
  <div class="commit file-history-tease js-blob-contributors-content" data-path="include/uv-private/ngx-queue.h/">
    <img class="main-avatar" height="24" src="https://secure.gravatar.com/avatar/ecd82262b3892441fa34fb04198162a7?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
    <span class="author"><a href="/trondn">trondn</a></span>
    <time class="js-relative-date" datetime="2012-08-08T16:09:09-07:00" title="2012-08-08 16:09:09">August 08, 2012</time>
    <div class="commit-title">
        <a href="/joyent/libuv/commit/cbb930024fc86aaf4edfbce71ea39b5ea520e973" class="message">Allow headers to be included with -Werror and -Wundef</a>
    </div>

    <div class="participation">
      <p class="quickstat"><a href="#blob_contributors_box" rel="facebox"><strong>3</strong> contributors</a></p>
          <a class="avatar tooltipped downwards" title="bnoordhuis" href="/joyent/libuv/commits/master/include/uv-private/ngx-queue.h?author=bnoordhuis"><img height="20" src="https://secure.gravatar.com/avatar/3d43d9038ab645ecb2e3a1df2951d30a?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="20" /></a>
    <a class="avatar tooltipped downwards" title="ry" href="/joyent/libuv/commits/master/include/uv-private/ngx-queue.h?author=ry"><img height="20" src="https://secure.gravatar.com/avatar/b984299ceb40752b58146714eb192554?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="20" /></a>
    <a class="avatar tooltipped downwards" title="trondn" href="/joyent/libuv/commits/master/include/uv-private/ngx-queue.h?author=trondn"><img height="20" src="https://secure.gravatar.com/avatar/ecd82262b3892441fa34fb04198162a7?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="20" /></a>


    </div>
    <div id="blob_contributors_box" style="display:none">
      <h2>Users on GitHub who have contributed to this file</h2>
      <ul class="facebox-user-list">
        <li>
          <img height="24" src="https://secure.gravatar.com/avatar/3d43d9038ab645ecb2e3a1df2951d30a?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
          <a href="/bnoordhuis">bnoordhuis</a>
        </li>
        <li>
          <img height="24" src="https://secure.gravatar.com/avatar/b984299ceb40752b58146714eb192554?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
          <a href="/ry">ry</a>
        </li>
        <li>
          <img height="24" src="https://secure.gravatar.com/avatar/ecd82262b3892441fa34fb04198162a7?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
          <a href="/trondn">trondn</a>
        </li>
      </ul>
    </div>
  </div>


    <div class="frames">
      <div class="frame frame-center" data-path="include/uv-private/ngx-queue.h/" data-permalink-url="/joyent/libuv/blob/ea8db64559680b589196b1ae01152c35d2232c41/include/uv-private/ngx-queue.h" data-title="libuv/include/uv-private/ngx-queue.h at master · joyent/libuv · GitHub" data-type="blob">

        <div id="files" class="bubble">
          <div class="file">
            <div class="meta">
              <div class="info">
                <span class="icon"><b class="mini-icon mini-icon-text-file"></b></span>
                <span class="mode" title="File Mode">file</span>
                  <span>109 lines (66 sloc)</span>
                <span>3.585 kb</span>
              </div>
              <ul class="button-group actions">
                  <li>
                    <a class="grouped-button file-edit-link minibutton bigger lighter js-rewrite-sha" href="/joyent/libuv/edit/ea8db64559680b589196b1ae01152c35d2232c41/include/uv-private/ngx-queue.h" data-method="post" rel="nofollow" data-hotkey="e">Edit</a>
                  </li>
                <li>
                  <a href="/joyent/libuv/raw/master/include/uv-private/ngx-queue.h" class="minibutton grouped-button bigger lighter" id="raw-url">Raw</a>
                </li>
                  <li>
                    <a href="/joyent/libuv/blame/master/include/uv-private/ngx-queue.h" class="minibutton grouped-button bigger lighter">Blame</a>
                  </li>
                <li>
                  <a href="/joyent/libuv/commits/master/include/uv-private/ngx-queue.h" class="minibutton grouped-button bigger lighter" rel="nofollow">History</a>
                </li>
              </ul>
            </div>
              <div class="data type-objective-c">
      <table cellpadding="0" cellspacing="0" class="lines">
        <tr>
          <td>
            <pre class="line_numbers"><span id="L1" rel="#L1">1</span>
<span id="L2" rel="#L2">2</span>
<span id="L3" rel="#L3">3</span>
<span id="L4" rel="#L4">4</span>
<span id="L5" rel="#L5">5</span>
<span id="L6" rel="#L6">6</span>
<span id="L7" rel="#L7">7</span>
<span id="L8" rel="#L8">8</span>
<span id="L9" rel="#L9">9</span>
<span id="L10" rel="#L10">10</span>
<span id="L11" rel="#L11">11</span>
<span id="L12" rel="#L12">12</span>
<span id="L13" rel="#L13">13</span>
<span id="L14" rel="#L14">14</span>
<span id="L15" rel="#L15">15</span>
<span id="L16" rel="#L16">16</span>
<span id="L17" rel="#L17">17</span>
<span id="L18" rel="#L18">18</span>
<span id="L19" rel="#L19">19</span>
<span id="L20" rel="#L20">20</span>
<span id="L21" rel="#L21">21</span>
<span id="L22" rel="#L22">22</span>
<span id="L23" rel="#L23">23</span>
<span id="L24" rel="#L24">24</span>
<span id="L25" rel="#L25">25</span>
<span id="L26" rel="#L26">26</span>
<span id="L27" rel="#L27">27</span>
<span id="L28" rel="#L28">28</span>
<span id="L29" rel="#L29">29</span>
<span id="L30" rel="#L30">30</span>
<span id="L31" rel="#L31">31</span>
<span id="L32" rel="#L32">32</span>
<span id="L33" rel="#L33">33</span>
<span id="L34" rel="#L34">34</span>
<span id="L35" rel="#L35">35</span>
<span id="L36" rel="#L36">36</span>
<span id="L37" rel="#L37">37</span>
<span id="L38" rel="#L38">38</span>
<span id="L39" rel="#L39">39</span>
<span id="L40" rel="#L40">40</span>
<span id="L41" rel="#L41">41</span>
<span id="L42" rel="#L42">42</span>
<span id="L43" rel="#L43">43</span>
<span id="L44" rel="#L44">44</span>
<span id="L45" rel="#L45">45</span>
<span id="L46" rel="#L46">46</span>
<span id="L47" rel="#L47">47</span>
<span id="L48" rel="#L48">48</span>
<span id="L49" rel="#L49">49</span>
<span id="L50" rel="#L50">50</span>
<span id="L51" rel="#L51">51</span>
<span id="L52" rel="#L52">52</span>
<span id="L53" rel="#L53">53</span>
<span id="L54" rel="#L54">54</span>
<span id="L55" rel="#L55">55</span>
<span id="L56" rel="#L56">56</span>
<span id="L57" rel="#L57">57</span>
<span id="L58" rel="#L58">58</span>
<span id="L59" rel="#L59">59</span>
<span id="L60" rel="#L60">60</span>
<span id="L61" rel="#L61">61</span>
<span id="L62" rel="#L62">62</span>
<span id="L63" rel="#L63">63</span>
<span id="L64" rel="#L64">64</span>
<span id="L65" rel="#L65">65</span>
<span id="L66" rel="#L66">66</span>
<span id="L67" rel="#L67">67</span>
<span id="L68" rel="#L68">68</span>
<span id="L69" rel="#L69">69</span>
<span id="L70" rel="#L70">70</span>
<span id="L71" rel="#L71">71</span>
<span id="L72" rel="#L72">72</span>
<span id="L73" rel="#L73">73</span>
<span id="L74" rel="#L74">74</span>
<span id="L75" rel="#L75">75</span>
<span id="L76" rel="#L76">76</span>
<span id="L77" rel="#L77">77</span>
<span id="L78" rel="#L78">78</span>
<span id="L79" rel="#L79">79</span>
<span id="L80" rel="#L80">80</span>
<span id="L81" rel="#L81">81</span>
<span id="L82" rel="#L82">82</span>
<span id="L83" rel="#L83">83</span>
<span id="L84" rel="#L84">84</span>
<span id="L85" rel="#L85">85</span>
<span id="L86" rel="#L86">86</span>
<span id="L87" rel="#L87">87</span>
<span id="L88" rel="#L88">88</span>
<span id="L89" rel="#L89">89</span>
<span id="L90" rel="#L90">90</span>
<span id="L91" rel="#L91">91</span>
<span id="L92" rel="#L92">92</span>
<span id="L93" rel="#L93">93</span>
<span id="L94" rel="#L94">94</span>
<span id="L95" rel="#L95">95</span>
<span id="L96" rel="#L96">96</span>
<span id="L97" rel="#L97">97</span>
<span id="L98" rel="#L98">98</span>
<span id="L99" rel="#L99">99</span>
<span id="L100" rel="#L100">100</span>
<span id="L101" rel="#L101">101</span>
<span id="L102" rel="#L102">102</span>
<span id="L103" rel="#L103">103</span>
<span id="L104" rel="#L104">104</span>
<span id="L105" rel="#L105">105</span>
<span id="L106" rel="#L106">106</span>
<span id="L107" rel="#L107">107</span>
<span id="L108" rel="#L108">108</span>
</pre>
          </td>
          <td width="100%">
                <div class="highlight"><pre><div class='line' id='LC1'><br/></div><div class='line' id='LC2'><span class="cm">/*</span></div><div class='line' id='LC3'><span class="cm"> * Copyright (C) Igor Sysoev</span></div><div class='line' id='LC4'><span class="cm"> */</span></div><div class='line' id='LC5'><br/></div><div class='line' id='LC6'><br/></div><div class='line' id='LC7'><span class="cp">#ifndef NGX_QUEUE_H_INCLUDED_</span></div><div class='line' id='LC8'><span class="cp">#define NGX_QUEUE_H_INCLUDED_</span></div><div class='line' id='LC9'><br/></div><div class='line' id='LC10'><br/></div><div class='line' id='LC11'><span class="k">typedef</span> <span class="k">struct</span> <span class="n">ngx_queue_s</span>  <span class="n">ngx_queue_t</span><span class="p">;</span></div><div class='line' id='LC12'><br/></div><div class='line' id='LC13'><span class="k">struct</span> <span class="n">ngx_queue_s</span> <span class="p">{</span></div><div class='line' id='LC14'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">ngx_queue_t</span>  <span class="o">*</span><span class="n">prev</span><span class="p">;</span></div><div class='line' id='LC15'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">ngx_queue_t</span>  <span class="o">*</span><span class="n">next</span><span class="p">;</span></div><div class='line' id='LC16'><span class="p">};</span></div><div class='line' id='LC17'><br/></div><div class='line' id='LC18'><br/></div><div class='line' id='LC19'><span class="cp">#define ngx_queue_init(q)                                                     \</span></div><div class='line' id='LC20'><span class="cp">    (q)-&gt;prev = q;                                                            \</span></div><div class='line' id='LC21'><span class="cp">    (q)-&gt;next = q</span></div><div class='line' id='LC22'><br/></div><div class='line' id='LC23'><br/></div><div class='line' id='LC24'><span class="cp">#define ngx_queue_empty(h)                                                    \</span></div><div class='line' id='LC25'><span class="cp">    (h == (h)-&gt;prev)</span></div><div class='line' id='LC26'><br/></div><div class='line' id='LC27'><br/></div><div class='line' id='LC28'><span class="cp">#define ngx_queue_insert_head(h, x)                                           \</span></div><div class='line' id='LC29'><span class="cp">    (x)-&gt;next = (h)-&gt;next;                                                    \</span></div><div class='line' id='LC30'><span class="cp">    (x)-&gt;next-&gt;prev = x;                                                      \</span></div><div class='line' id='LC31'><span class="cp">    (x)-&gt;prev = h;                                                            \</span></div><div class='line' id='LC32'><span class="cp">    (h)-&gt;next = x</span></div><div class='line' id='LC33'><br/></div><div class='line' id='LC34'><br/></div><div class='line' id='LC35'><span class="cp">#define ngx_queue_insert_after   ngx_queue_insert_head</span></div><div class='line' id='LC36'><br/></div><div class='line' id='LC37'><br/></div><div class='line' id='LC38'><span class="cp">#define ngx_queue_insert_tail(h, x)                                           \</span></div><div class='line' id='LC39'><span class="cp">    (x)-&gt;prev = (h)-&gt;prev;                                                    \</span></div><div class='line' id='LC40'><span class="cp">    (x)-&gt;prev-&gt;next = x;                                                      \</span></div><div class='line' id='LC41'><span class="cp">    (x)-&gt;next = h;                                                            \</span></div><div class='line' id='LC42'><span class="cp">    (h)-&gt;prev = x</span></div><div class='line' id='LC43'><br/></div><div class='line' id='LC44'><br/></div><div class='line' id='LC45'><span class="cp">#define ngx_queue_head(h)                                                     \</span></div><div class='line' id='LC46'><span class="cp">    (h)-&gt;next</span></div><div class='line' id='LC47'><br/></div><div class='line' id='LC48'><br/></div><div class='line' id='LC49'><span class="cp">#define ngx_queue_last(h)                                                     \</span></div><div class='line' id='LC50'><span class="cp">    (h)-&gt;prev</span></div><div class='line' id='LC51'><br/></div><div class='line' id='LC52'><br/></div><div class='line' id='LC53'><span class="cp">#define ngx_queue_sentinel(h)                                                 \</span></div><div class='line' id='LC54'><span class="cp">    (h)</span></div><div class='line' id='LC55'><br/></div><div class='line' id='LC56'><br/></div><div class='line' id='LC57'><span class="cp">#define ngx_queue_next(q)                                                     \</span></div><div class='line' id='LC58'><span class="cp">    (q)-&gt;next</span></div><div class='line' id='LC59'><br/></div><div class='line' id='LC60'><br/></div><div class='line' id='LC61'><span class="cp">#define ngx_queue_prev(q)                                                     \</span></div><div class='line' id='LC62'><span class="cp">    (q)-&gt;prev</span></div><div class='line' id='LC63'><br/></div><div class='line' id='LC64'><br/></div><div class='line' id='LC65'><span class="cp">#if defined(NGX_DEBUG)</span></div><div class='line' id='LC66'><br/></div><div class='line' id='LC67'><span class="cp">#define ngx_queue_remove(x)                                                   \</span></div><div class='line' id='LC68'><span class="cp">    (x)-&gt;next-&gt;prev = (x)-&gt;prev;                                              \</span></div><div class='line' id='LC69'><span class="cp">    (x)-&gt;prev-&gt;next = (x)-&gt;next;                                              \</span></div><div class='line' id='LC70'><span class="cp">    (x)-&gt;prev = NULL;                                                         \</span></div><div class='line' id='LC71'><span class="cp">    (x)-&gt;next = NULL</span></div><div class='line' id='LC72'><br/></div><div class='line' id='LC73'><span class="cp">#else</span></div><div class='line' id='LC74'><br/></div><div class='line' id='LC75'><span class="cp">#define ngx_queue_remove(x)                                                   \</span></div><div class='line' id='LC76'><span class="cp">    (x)-&gt;next-&gt;prev = (x)-&gt;prev;                                              \</span></div><div class='line' id='LC77'><span class="cp">    (x)-&gt;prev-&gt;next = (x)-&gt;next</span></div><div class='line' id='LC78'><br/></div><div class='line' id='LC79'><span class="cp">#endif</span></div><div class='line' id='LC80'><br/></div><div class='line' id='LC81'><br/></div><div class='line' id='LC82'><span class="cp">#define ngx_queue_split(h, q, n)                                              \</span></div><div class='line' id='LC83'><span class="cp">    (n)-&gt;prev = (h)-&gt;prev;                                                    \</span></div><div class='line' id='LC84'><span class="cp">    (n)-&gt;prev-&gt;next = n;                                                      \</span></div><div class='line' id='LC85'><span class="cp">    (n)-&gt;next = q;                                                            \</span></div><div class='line' id='LC86'><span class="cp">    (h)-&gt;prev = (q)-&gt;prev;                                                    \</span></div><div class='line' id='LC87'><span class="cp">    (h)-&gt;prev-&gt;next = h;                                                      \</span></div><div class='line' id='LC88'><span class="cp">    (q)-&gt;prev = n;</span></div><div class='line' id='LC89'><br/></div><div class='line' id='LC90'><br/></div><div class='line' id='LC91'><span class="cp">#define ngx_queue_add(h, n)                                                   \</span></div><div class='line' id='LC92'><span class="cp">    (h)-&gt;prev-&gt;next = (n)-&gt;next;                                              \</span></div><div class='line' id='LC93'><span class="cp">    (n)-&gt;next-&gt;prev = (h)-&gt;prev;                                              \</span></div><div class='line' id='LC94'><span class="cp">    (h)-&gt;prev = (n)-&gt;prev;                                                    \</span></div><div class='line' id='LC95'><span class="cp">    (h)-&gt;prev-&gt;next = h;</span></div><div class='line' id='LC96'><br/></div><div class='line' id='LC97'><br/></div><div class='line' id='LC98'><span class="cp">#define ngx_queue_data(q, type, link)                                         \</span></div><div class='line' id='LC99'><span class="cp">    (type *) ((unsigned char *) q - offsetof(type, link))</span></div><div class='line' id='LC100'><br/></div><div class='line' id='LC101'><br/></div><div class='line' id='LC102'><span class="cp">#define ngx_queue_foreach(q, h)                                               \</span></div><div class='line' id='LC103'><span class="cp">    for ((q) = ngx_queue_head(h);                                             \</span></div><div class='line' id='LC104'><span class="cp">         (q) != ngx_queue_sentinel(h);                                        \</span></div><div class='line' id='LC105'><span class="cp">         (q) = ngx_queue_next(q))</span></div><div class='line' id='LC106'><br/></div><div class='line' id='LC107'><br/></div><div class='line' id='LC108'><span class="cp">#endif </span><span class="cm">/* NGX_QUEUE_H_INCLUDED_ */</span><span class="cp"></span></div></pre></div>
          </td>
        </tr>
      </table>
  </div>

          </div>
        </div>
      </div>
    </div>

  </div>

<div class="frame frame-loading large-loading-area" style="display:none;" data-tree-list-url="/joyent/libuv/tree-list/ea8db64559680b589196b1ae01152c35d2232c41" data-blob-url-prefix="/joyent/libuv/blob/ea8db64559680b589196b1ae01152c35d2232c41">
  <img src="https://a248.e.akamai.net/assets.github.com/images/spinners/octocat-spinner-128.gif?1347543532" height="64" width="64">
</div>

        </div>
      </div>
      <div class="context-overlay"></div>
    </div>

      <div id="footer-push"></div><!-- hack for sticky footer -->
    </div><!-- end of wrapper - hack for sticky footer -->

      <!-- footer -->
      <div id="footer" >
        
  <div class="upper_footer">
     <div class="container clearfix">

       <!--[if IE]><h4 id="blacktocat_ie">GitHub Links</h4><![endif]-->
       <![if !IE]><h4 id="blacktocat">GitHub Links</h4><![endif]>

       <ul class="footer_nav">
         <h4>GitHub</h4>
         <li><a href="https://github.com/about">About</a></li>
         <li><a href="https://github.com/blog">Blog</a></li>
         <li><a href="https://github.com/features">Features</a></li>
         <li><a href="https://github.com/contact">Contact &amp; Support</a></li>
         <li><a href="https://github.com/training">Training</a></li>
         <li><a href="http://enterprise.github.com/">GitHub Enterprise</a></li>
         <li><a href="http://status.github.com/">Site Status</a></li>
       </ul>

       <ul class="footer_nav">
         <h4>Clients</h4>
         <li><a href="http://mac.github.com/">GitHub for Mac</a></li>
         <li><a href="http://windows.github.com/">GitHub for Windows</a></li>
         <li><a href="http://eclipse.github.com/">GitHub for Eclipse</a></li>
         <li><a href="http://mobile.github.com/">GitHub Mobile Apps</a></li>
       </ul>

       <ul class="footer_nav">
         <h4>Tools</h4>
         <li><a href="http://get.gaug.es/">Gauges: Web analytics</a></li>
         <li><a href="http://speakerdeck.com">Speaker Deck: Presentations</a></li>
         <li><a href="https://gist.github.com">Gist: Code snippets</a></li>

         <h4 class="second">Extras</h4>
         <li><a href="http://jobs.github.com/">Job Board</a></li>
         <li><a href="http://shop.github.com/">GitHub Shop</a></li>
         <li><a href="http://octodex.github.com/">The Octodex</a></li>
       </ul>

       <ul class="footer_nav">
         <h4>Documentation</h4>
         <li><a href="http://help.github.com/">GitHub Help</a></li>
         <li><a href="http://developer.github.com/">Developer API</a></li>
         <li><a href="http://github.github.com/github-flavored-markdown/">GitHub Flavored Markdown</a></li>
         <li><a href="http://pages.github.com/">GitHub Pages</a></li>
       </ul>

     </div><!-- /.site -->
  </div><!-- /.upper_footer -->

<div class="lower_footer">
  <div class="container clearfix">
    <!--[if IE]><div id="legal_ie"><![endif]-->
    <![if !IE]><div id="legal"><![endif]>
      <ul>
          <li><a href="https://github.com/site/terms">Terms of Service</a></li>
          <li><a href="https://github.com/site/privacy">Privacy</a></li>
          <li><a href="https://github.com/security">Security</a></li>
      </ul>

      <p>&copy; 2012 <span title="0.20458s from fe15.rs.github.com">GitHub</span> Inc. All rights reserved.</p>
    </div><!-- /#legal or /#legal_ie-->

  </div><!-- /.site -->
</div><!-- /.lower_footer -->

      </div><!-- /#footer -->

    

<div id="keyboard_shortcuts_pane" class="instapaper_ignore readability-extra" style="display:none">
  <h2>Keyboard Shortcuts <small><a href="#" class="js-see-all-keyboard-shortcuts">(see all)</a></small></h2>

  <div class="columns threecols">
    <div class="column first">
      <h3>Site wide shortcuts</h3>
      <dl class="keyboard-mappings">
        <dt>s</dt>
        <dd>Focus site search</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt>?</dt>
        <dd>Bring up this help dialog</dd>
      </dl>
    </div><!-- /.column.first -->

    <div class="column middle" style='display:none'>
      <h3>Commit list</h3>
      <dl class="keyboard-mappings">
        <dt>j</dt>
        <dd>Move selection down</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt>k</dt>
        <dd>Move selection up</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt>c <em>or</em> o <em>or</em> enter</dt>
        <dd>Open commit</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt>y</dt>
        <dd>Expand URL to its canonical form</dd>
      </dl>
    </div><!-- /.column.first -->

    <div class="column last js-hidden-pane" style='display:none'>
      <h3>Pull request list</h3>
      <dl class="keyboard-mappings">
        <dt>j</dt>
        <dd>Move selection down</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt>k</dt>
        <dd>Move selection up</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt>o <em>or</em> enter</dt>
        <dd>Open issue</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt><span class="platform-mac">⌘</span><span class="platform-other">ctrl</span> <em>+</em> enter</dt>
        <dd>Submit comment</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt><span class="platform-mac">⌘</span><span class="platform-other">ctrl</span> <em>+</em> shift p</dt>
        <dd>Preview comment</dd>
      </dl>
    </div><!-- /.columns.last -->

  </div><!-- /.columns.equacols -->

  <div class="js-hidden-pane" style='display:none'>
    <div class="rule"></div>

    <h3>Issues</h3>

    <div class="columns threecols">
      <div class="column first">
        <dl class="keyboard-mappings">
          <dt>j</dt>
          <dd>Move selection down</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>k</dt>
          <dd>Move selection up</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>x</dt>
          <dd>Toggle selection</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>o <em>or</em> enter</dt>
          <dd>Open issue</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt><span class="platform-mac">⌘</span><span class="platform-other">ctrl</span> <em>+</em> enter</dt>
          <dd>Submit comment</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt><span class="platform-mac">⌘</span><span class="platform-other">ctrl</span> <em>+</em> shift p</dt>
          <dd>Preview comment</dd>
        </dl>
      </div><!-- /.column.first -->
      <div class="column last">
        <dl class="keyboard-mappings">
          <dt>c</dt>
          <dd>Create issue</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>l</dt>
          <dd>Create label</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>i</dt>
          <dd>Back to inbox</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>u</dt>
          <dd>Back to issues</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>/</dt>
          <dd>Focus issues search</dd>
        </dl>
      </div>
    </div>
  </div>

  <div class="js-hidden-pane" style='display:none'>
    <div class="rule"></div>

    <h3>Issues Dashboard</h3>

    <div class="columns threecols">
      <div class="column first">
        <dl class="keyboard-mappings">
          <dt>j</dt>
          <dd>Move selection down</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>k</dt>
          <dd>Move selection up</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>o <em>or</em> enter</dt>
          <dd>Open issue</dd>
        </dl>
      </div><!-- /.column.first -->
    </div>
  </div>

  <div class="js-hidden-pane" style='display:none'>
    <div class="rule"></div>

    <h3>Network Graph</h3>
    <div class="columns equacols">
      <div class="column first">
        <dl class="keyboard-mappings">
          <dt><span class="badmono">←</span> <em>or</em> h</dt>
          <dd>Scroll left</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt><span class="badmono">→</span> <em>or</em> l</dt>
          <dd>Scroll right</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt><span class="badmono">↑</span> <em>or</em> k</dt>
          <dd>Scroll up</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt><span class="badmono">↓</span> <em>or</em> j</dt>
          <dd>Scroll down</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>t</dt>
          <dd>Toggle visibility of head labels</dd>
        </dl>
      </div><!-- /.column.first -->
      <div class="column last">
        <dl class="keyboard-mappings">
          <dt>shift <span class="badmono">←</span> <em>or</em> shift h</dt>
          <dd>Scroll all the way left</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>shift <span class="badmono">→</span> <em>or</em> shift l</dt>
          <dd>Scroll all the way right</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>shift <span class="badmono">↑</span> <em>or</em> shift k</dt>
          <dd>Scroll all the way up</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>shift <span class="badmono">↓</span> <em>or</em> shift j</dt>
          <dd>Scroll all the way down</dd>
        </dl>
      </div><!-- /.column.last -->
    </div>
  </div>

  <div class="js-hidden-pane" >
    <div class="rule"></div>
    <div class="columns threecols">
      <div class="column first js-hidden-pane" >
        <h3>Source Code Browsing</h3>
        <dl class="keyboard-mappings">
          <dt>t</dt>
          <dd>Activates the file finder</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>l</dt>
          <dd>Jump to line</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>w</dt>
          <dd>Switch branch/tag</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>y</dt>
          <dd>Expand URL to its canonical form</dd>
        </dl>
      </div>
    </div>
  </div>

  <div class="js-hidden-pane" style='display:none'>
    <div class="rule"></div>
    <div class="columns threecols">
      <div class="column first">
        <h3>Browsing Commits</h3>
        <dl class="keyboard-mappings">
          <dt><span class="platform-mac">⌘</span><span class="platform-other">ctrl</span> <em>+</em> enter</dt>
          <dd>Submit comment</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>escape</dt>
          <dd>Close form</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>p</dt>
          <dd>Parent commit</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>o</dt>
          <dd>Other parent commit</dd>
        </dl>
      </div>
    </div>
  </div>

  <div class="js-hidden-pane" style='display:none'>
    <div class="rule"></div>
    <h3>Notifications</h3>

    <div class="columns threecols">
      <div class="column first">
        <dl class="keyboard-mappings">
          <dt>j</dt>
          <dd>Move selection down</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>k</dt>
          <dd>Move selection up</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>o <em>or</em> enter</dt>
          <dd>Open notification</dd>
        </dl>
      </div><!-- /.column.first -->

      <div class="column second">
        <dl class="keyboard-mappings">
          <dt>e <em>or</em> shift i <em>or</em> y</dt>
          <dd>Mark as read</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>shift m</dt>
          <dd>Mute thread</dd>
        </dl>
      </div><!-- /.column.first -->
    </div>
  </div>

</div>

    <div id="markdown-help" class="instapaper_ignore readability-extra">
  <h2>Markdown Cheat Sheet</h2>

  <div class="cheatsheet-content">

  <div class="mod">
    <div class="col">
      <h3>Format Text</h3>
      <p>Headers</p>
      <pre>
# This is an &lt;h1&gt; tag
## This is an &lt;h2&gt; tag
###### This is an &lt;h6&gt; tag</pre>
     <p>Text styles</p>
     <pre>
*This text will be italic*
_This will also be italic_
**This text will be bold**
__This will also be bold__

*You **can** combine them*
</pre>
    </div>
    <div class="col">
      <h3>Lists</h3>
      <p>Unordered</p>
      <pre>
* Item 1
* Item 2
  * Item 2a
  * Item 2b</pre>
     <p>Ordered</p>
     <pre>
1. Item 1
2. Item 2
3. Item 3
   * Item 3a
   * Item 3b</pre>
    </div>
    <div class="col">
      <h3>Miscellaneous</h3>
      <p>Images</p>
      <pre>
![GitHub Logo](/images/logo.png)
Format: ![Alt Text](url)
</pre>
     <p>Links</p>
     <pre>
http://github.com - automatic!
[GitHub](http://github.com)</pre>
<p>Blockquotes</p>
     <pre>
As Kanye West said:

> We're living the future so
> the present is our past.
</pre>
    </div>
  </div>
  <div class="rule"></div>

  <h3>Code Examples in Markdown</h3>
  <div class="col">
      <p>Syntax highlighting with <a href="http://github.github.com/github-flavored-markdown/" title="GitHub Flavored Markdown" target="_blank">GFM</a></p>
      <pre>
```javascript
function fancyAlert(arg) {
  if(arg) {
    $.facebox({div:'#foo'})
  }
}
```</pre>
    </div>
    <div class="col">
      <p>Or, indent your code 4 spaces</p>
      <pre>
Here is a Python code example
without syntax highlighting:

    def foo:
      if not bar:
        return true</pre>
    </div>
    <div class="col">
      <p>Inline code for comments</p>
      <pre>
I think you should use an
`&lt;addr&gt;` element here instead.</pre>
    </div>
  </div>

  </div>
</div>


    <div id="ajax-error-message" class="flash flash-error">
      <span class="mini-icon mini-icon-exclamation"></span>
      Something went wrong with that request. Please try again.
      <a href="#" class="mini-icon mini-icon-remove-close ajax-error-dismiss"></a>
    </div>

    <div id="logo-popup">
      <h2>Looking for the GitHub logo?</h2>
      <ul>
        <li>
          <h4>GitHub Logo</h4>
          <a href="http://github-media-downloads.s3.amazonaws.com/GitHub_Logos.zip"><img alt="Github_logo" src="https://a248.e.akamai.net/assets.github.com/images/modules/about_page/github_logo.png?1329920549" /></a>
          <a href="http://github-media-downloads.s3.amazonaws.com/GitHub_Logos.zip" class="minibutton download">Download</a>
        </li>
        <li>
          <h4>The Octocat</h4>
          <a href="http://github-media-downloads.s3.amazonaws.com/Octocats.zip"><img alt="Octocat" src="https://a248.e.akamai.net/assets.github.com/images/modules/about_page/octocat.png?1329920549" /></a>
          <a href="http://github-media-downloads.s3.amazonaws.com/Octocats.zip" class="minibutton download">Download</a>
        </li>
      </ul>
    </div>

    
    
    <span id='server_response_time' data-time='0.21164' data-host='fe15'></span>
    
  </body>
</html>

