import Control.Monad

data Id a = Id a deriving Show

instance Functor Id where
    fmap f (Id x)   = Id (f x)

instance Applicative Id where
    pure x          = Id x
    Id f <*> Id x   = Id (f x)

instance Monad Id where
    (Id x) >>= f    = f x
